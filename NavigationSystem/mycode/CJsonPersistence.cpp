/*
 * CJsonPersistence.cpp
 *
 *  Created on: 09.01.2017
 *      Author: stbidula
 */
using namespace std;
#include "CJsonPersistence.h"
#include <exception>

using namespace APT;

void CJsonPersistence::setMediaName(string filename)
{
	m_filename = filename;
}

bool CJsonPersistence::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDB)
{
	string name;
	double latitude;
	double longitude;
	string description;
	t_poi type;

	//opening the file from static memory
	m_datafile.open((m_filename).c_str(), fstream::out);
	if (m_datafile.is_open())
	{
		//creating a temporary to store the waypoint database
		map<string, CWaypoint> tmp_wpmap = waypointDb.getMap();
		map<string, CWaypoint>::iterator itrwp;
		m_datafile << "{\n" << " \"waypoints\": [" << endl;
		for (itrwp = tmp_wpmap.begin(); itrwp != tmp_wpmap.end(); itrwp++)
		{
			((*itrwp).second).getAllDataByReference(name, latitude, longitude);

			m_datafile << "\t" << "{" << endl << "\t" << " \"name\" :" << " "
					<< "\"" << name << "\"" << "," << endl << "\t"
					<< " \"latitude\" :" << " " << latitude << "," << endl
					<< "\t" << " \"longitude\" :" << " " << longitude << endl
					<< "\t" << "}";
			if (itrwp == --tmp_wpmap.end())
			{
				m_datafile << endl;
			}
			else
			{
				m_datafile << "," << endl;
			}
		}
		m_datafile << "]," << endl;

		//creating temporary map to store poi database
		map<string, CPOI> tmp_poidata = poiDB.getMap();
		map<string, CPOI>::iterator itrpoi;
		m_datafile << " \"pois\": [" << endl;
		for (itrpoi = tmp_poidata.begin(); itrpoi != tmp_poidata.end();
				itrpoi++)
		{
			((*itrpoi).second).getAllDataByReference(name, latitude, longitude,
					type, description);

			m_datafile << "\t" << "{" << endl << "\t" << " \"name\" :" << " "
					<< "\"" << name << "\"" << "," << endl << "\t"
					<< " \"latitude\" :" << " " << latitude << "," << endl
					<< "\t" << " \"longitude\" :" << " " << longitude<<"," << endl;
			switch (type)
			{
			case RESTAURANT:

				m_datafile << "\t" << " \"type\" :" << " " << "\""
						<< "RESTAURANT" << "\"" << "," << endl;
				break;
			case HOSPITAL:

				m_datafile << "\t" << " \"type\" :" << " " << "\"" << "HOSPITAL"
						<< "\"" << "," << endl;
				break;
			case SIGHTSEEING:

				m_datafile << "\t" << " \"type\" :" << " " << "\""
						<< "SIGHTSEEING" << "\"" << "," << endl;
				break;
			default:
				m_datafile << "\t" << " \"type\" :" << " " << "\"" << "NOTYPE"
						<< "\"" << "," << endl;
				break;

			}

			m_datafile << "\t" << " \"description\" :" << " " << "\""
					<< description << "\"" << "," << endl << "\t" << "}";
			if (itrpoi == --tmp_poidata.end()) {
				m_datafile << endl;
			}
			else
			{
				m_datafile << "," << endl;
			}
		}
		m_datafile << "\t" << "]" << endl << "}";

	}
	else
	{
		cout << "error:cannot create file!!" << endl;
		return false;
	}
	//closing file after writing
	m_datafile.close();

	return false;
}

bool CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode)
{
	//bool databaseflag=false;
	bool nameSetFlag=false;
	bool latitudeSetFlag=false;
	bool longitudeSetFlag=false;
	bool typeSetFlag=false;
	bool descriptionSetFlag=false;

	int nameFlag=0;
	int latitudeFlag=0;
	int longitudeFlag=0;
	int typeFlag=0;
	int descriptionFlag=0;
	int nameSeparator=0;
//	int errorFlag=0;
	string incomingName="";
	string incomingValue = "";
	string m_name="";
	string m_description="";
	double m_latitude=0;
	double m_longitude=0;
	string m_typeString="";
	t_poi m_type;
	string dbName="";

		//declaring buffer in order to generate an istream object
		filebuf buf_file;


		CJsonToken* jsonToken=NULL;
		CJsonStringToken* stringToken=NULL;

		//opening file
		buf_file.open(("navigationdata"), fstream::in);

		if(!(buf_file.is_open()))
		{
		cout<<"error:cannot open jsonfile!!"<<endl;
		}
		else
		{
			//cout<<"file opening suceess!!"<<endl;
			//for creating an istream object buffer is used for CJsonScanner class
			istream is(&buf_file);
			//Setting the the pointer of the current  CJsonScanner to NULL
			CJsonScanner jsonScanner(is);
			//initializing the statemachine
			int currentState=WAITING_FOR_FIRST_TOKEN;
			int nextState=WAITING_FOR_FIRST_TOKEN;
			//trying to get first token from json file


			//check if this can be used??
			while(!is.eof())
			{
				try
				{
					jsonToken=jsonScanner.nextToken();
					if(jsonToken==NULL)
					{
						throw "null value";
					}
				}
				catch (const char* msg)
				{
					cout << msg <<endl;
					currentState=-1;


				}
				switch(currentState)
				{

				case WAITING_FOR_FIRST_TOKEN:

					if(jsonToken->getType()==CJsonToken::BEGIN_OBJECT)
					{
					//	cout<<"Is waiting for first token"<<endl;
						nextState=WAITING_FOR_DB_NAME;

					}
					else
					{
						//handle error if there is no {
						cout<<"error:no { !!"<<endl;
						nextState=READ_COMPLETE;
						return false;

					}
					//jsonToken=jsonScanner.nextToken();


					break;

				case WAITING_FOR_DB_NAME:
					//cout<<"Is waiting for db name"<<endl;
					if (jsonToken->getType()==CJsonToken::STRING)
					{
						stringToken= dynamic_cast<CJsonStringToken*> (jsonToken);
						if(jsonToken==NULL)
						{
						//throw an error if there exist no database name

						}
						else
						{
						dbName=stringToken->getValue();
						//cout<<"Name:"<<dbName<<endl;
						}
						nextState=WAITING_FOR_DB_VERIFY;
					}
					else
					{
						//error expected string type of database
						cout<<"error:database name should be string in line:"
								<<jsonScanner.scannedLine()<<endl;
					}
					//jsonToken=jsonScanner.nextToken();
					break;


				case WAITING_FOR_DB_VERIFY:
					if (jsonToken->getType() == CJsonToken::NAME_SEPARATOR)
					{
					//	databaseflag=true;
					//	cout<<jsonScanner.scannedLine();
					//	cout<<"verified!"<<endl;
						nextState=WAITING_FOR_DB_BEGIN;
						//jsonToken=jsonScanner.nextToken();
					}
					else
					{
						//expected : after database name
						nextState=WAITING_FOR_DB_NAME;
						cout<<"error: expected : after"<<dbName<<endl;
					}


					break;

				case WAITING_FOR_DB_BEGIN:
					if (jsonToken->getType()==CJsonToken::BEGIN_ARRAY)
					{
					//	cout<<"bingo"<<endl;
						nextState=WAITING_FOR_OBJ_BEGIN;
					}

					//jsonToken=jsonScanner.nextToken();
					break;

				case WAITING_FOR_OBJ_BEGIN:
					if (jsonToken->getType()==CJsonToken::BEGIN_OBJECT)
					{

						//cout<<"object { begins"<<endl;
						nextState=WAITING_FOR_ATTR_NAME;
					}
					else
					{
						nextState=-1;
					}
					//jsonToken=jsonScanner.nextToken();

					break;

				case WAITING_FOR_ATTR_NAME:
					if (jsonToken->getType()==CJsonToken::STRING)
					{

					try
					{
					 stringToken =dynamic_cast<CJsonStringToken*>(jsonToken);
					 if(stringToken==NULL)
					 {
						 throw "invalid string  type!!";
					 }
					}
					catch(const char* msg)
					{
						cout<<"error: "<<msg<<endl;
					}



					if (jsonToken == NULL)
					{
						//throw an error if there exist no name
						cout<<"Did it worked??"<<endl;
					} else {

						incomingName = stringToken->getValue();
					//	cout << incomingName << endl;


						nextState=WAITING_FOR_NAME_SEPARATOR;
					}

					}
					//jsonToken=jsonScanner.nextToken();
					break;

				case WAITING_FOR_NAME_SEPARATOR:
					if (jsonToken->getType()==CJsonToken::NAME_SEPARATOR)
					{
						nextState=WAITING_FOR_VALUE;
						nameSeparator++;
						if (incomingName == "name")
						{
							nameFlag = 1;
						}
						else if (incomingName == "latitude")
						{
							latitudeFlag = 1;
						}
						else if (incomingName == "longitude")
						{
							longitudeFlag = 1;
						}
						else if (incomingName == "type")
						{
							typeFlag = 1;
						}
						else if(incomingName == "description")
						{
							descriptionFlag = 1;
						}
						else
						{
			//				errorFlag = 1;
							cout<<"error: invalid! "<<incomingName
									<<"in the line: "<<jsonScanner.scannedLine();
						}
					}
					//jsonToken = jsonScanner.nextToken();
					break;

			case WAITING_FOR_VALUE:
				if (jsonToken->getType() == CJsonToken::STRING)
				{
					CJsonStringToken* stringToken =
							dynamic_cast<CJsonStringToken*>(jsonToken);
					if (jsonToken == NULL)
					{
						//throw an error if there exist no string value
					}
					else
					{
						//get the value of the json key
						incomingValue = stringToken->getValue();

						if(nameFlag==1)
						{
							m_name=incomingValue;
							nameFlag=0;
							nameSetFlag=true;
						}
						else if(typeFlag==1)
						{
							m_typeString=incomingValue;
							typeFlag=0;
							if(m_typeString=="RESTAURANT" )
							{
								m_type=RESTAURANT;
								typeSetFlag=true;

							}
							else if (m_typeString == "SIGHTSEEING")
							{
								m_type=SIGHTSEEING;
								typeSetFlag=true;
							}
							else if (m_typeString == "HOSPITAL")
							{
								m_type=HOSPITAL;
								typeSetFlag=true;
							}
							else
							{
								cout<<"error: type cannot be set!! Invalid "
										"format!!"<<endl;
								typeSetFlag=false;
							}
						}
						else if(descriptionFlag==1)
						{
							m_description=incomingValue;
							descriptionFlag=0;
							descriptionSetFlag=true;
						}
						else
						{
							cout<<"error: no matching incoming types!"<<endl;
						}
						nextState = WAITING_FOR_VALUE_SEPARATOR;
					}

				}
				else if (jsonToken->getType() == CJsonToken::NUMBER)
				{
					CJsonNumberToken* numberToken =
							dynamic_cast<CJsonNumberToken*>(jsonToken);
					if (jsonToken == NULL)
					{
						//throw an error if there exist no number value
					}
					else
					{
						double numberValue=0;
						numberValue = numberToken->getValue();
					//	cout << numberValue << endl;
						if(latitudeFlag==1)
						{
							m_latitude=numberValue;
							latitudeFlag=0;
							latitudeSetFlag=true;
						}
						else if(longitudeFlag==1)
						{
							m_longitude=numberValue;
							longitudeFlag=0;
							longitudeSetFlag=true;
						}
						else
						{
							//no proper reading
							cout<<"error: no matching incoming number types!"<<endl;
						}

						nextState = WAITING_FOR_VALUE_SEPARATOR;
					}
				}

				//jsonToken = jsonScanner.nextToken();

				break;

				case WAITING_FOR_VALUE_SEPARATOR:
					if (jsonToken->getType() == CJsonToken::VALUE_SEPARATOR)
					{
						nextState=WAITING_FOR_ATTR_NAME;
					}
					else if (jsonToken->getType() == CJsonToken::END_OBJECT)
					{
					//check if it is real database
					if (dbName == "waypoints")
					{
						if (nameSetFlag && latitudeSetFlag && longitudeSetFlag)
						{
							//if there is enough data, store the data to waypoint
							//database
							CWaypoint wayPoint(m_name, m_latitude, m_longitude);
							waypointDb.addWaypoint(wayPoint);
							cout<<"added"<<endl;
						}
						else
						{
							//no complete data found
							cout<<"error: incomplete data in: "<<dbName<<endl;
						}
						nameSetFlag=false;
						latitudeSetFlag=false;
						longitudeSetFlag=false;
					}

					else if (dbName == "pois")
						{
							if (nameSetFlag && latitudeSetFlag && longitudeSetFlag
									&& typeSetFlag && descriptionSetFlag)
							{
								//if there is enough data, store the data to
								//poidatabase
								CPOI poi(m_type,m_name,m_description, m_latitude,
										m_longitude);
								poiDb.addPoi(poi);
							}
							else
							{
								//no complete data found
								cout << "error: incomplete data in: " << dbName
										<< endl;
							}
							nameSetFlag=false;
							latitudeSetFlag=false;
							longitudeSetFlag=false;
							typeSetFlag=false;
							descriptionSetFlag=false;
					}
					else
					{
						cout<<"error: invalid db Name: "<<dbName<<endl;
					}
						nextState = WAITING_FOR_OBJ_SEPARATOR;
					}
					else
					{
					//what will be the next state? error handling
					//nextState=WAITING_FOR_OBJ_BEGIN;
						nextState=WAITING_FOR_VALUE_SEPARATOR;
					}
					//jsonToken = jsonScanner.nextToken();
					break;

				case WAITING_FOR_OBJ_SEPARATOR:
					if (jsonToken->getType() == CJsonToken::VALUE_SEPARATOR)

					{
						nextState=WAITING_FOR_OBJ_BEGIN;
					}
					else if(jsonToken->getType() == CJsonToken::END_ARRAY)
					{
						nextState=WAITING_FOR_ARRAY_SEPERATOR;
					}
			//do something here
					else if(jsonToken->getType() == CJsonToken::BEGIN_OBJECT)
					{
						nextState=WAITING_FOR_ATTR_NAME;
					}
					else
					{
						nextState=WAITING_FOR_OBJ_BEGIN;
					}
					//jsonToken = jsonScanner.nextToken();
					break;

				case WAITING_FOR_ARRAY_SEPERATOR:
					if (jsonToken->getType() == CJsonToken::VALUE_SEPARATOR)
					{
						nextState=WAITING_FOR_DB_NAME;
					//	cout<<"howcome??"<<dbName<<endl;

					}
					else if(jsonToken->getType() == CJsonToken::END_OBJECT)
					{
						nextState=READ_COMPLETE;

					}
					else
					{
						//verify this!!!
						nextState=WAITING_FOR_ARRAY_SEPERATOR;
					}
					//jsonToken = jsonScanner.nextToken();
					break;

				case READ_COMPLETE:
					//cout<<"howcome??"<<dbName<<endl;
					break;
				default:
					break;
				}
				currentState=nextState;
			}
		}
		buf_file.close();
		return true;

}
