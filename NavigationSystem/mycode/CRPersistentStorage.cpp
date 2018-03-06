using namespace std;
#include "CRPersistentStorage.h"

CRPersistentStorage::CRPersistentStorage()
{
	m_nameWp="";
	m_namePoi="";
}

CPersistentStorage::~CPersistentStorage()
{
	//destructor
}

void CRPersistentStorage::setMediaName(std::string name)
{
	//getting the name of the files where databases are stored
	m_nameWp=name+"-wp.txt";
	m_namePoi=name+"-poi.txt";
}

bool CRPersistentStorage::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDB)
{
	string name;
	double latitude;
	double longitude;
	string description;
	t_poi type;
	//opening the waypoint file from static memory
	m_wpFile.open((m_nameWp).c_str(), fstream::out);
	if(m_wpFile.is_open())
	{
		//creating a temporary to store the waypoint database
		map<string, CWaypoint> tmp_wpmap=waypointDb.getMap();
		map<string, CWaypoint>::iterator itrwp;

		for (itrwp = tmp_wpmap.begin();itrwp != tmp_wpmap.end(); itrwp++)
		{
			((*itrwp).second).getAllDataByReference(name,latitude,longitude);


			m_wpFile<<name<<";"<<latitude<<";"<<longitude<<endl;
		}
	}
	else
	{
		cout<<"error:cannot create waypoint file!!"<<endl;
		return false;
	}
	//closing file after writing
	m_wpFile.close();
	//opening the poi file from static memory
	m_poiFile.open((m_namePoi).c_str(), fstream::out);
	if(m_poiFile.is_open())
	{
		//creating temporary map to store poi database
		map<string, CPOI> tmp_poidata=poiDB.getMap();
		map<string, CPOI>::iterator itrpoi;
		for (itrpoi = tmp_poidata.begin();
						itrpoi != tmp_poidata.end(); itrpoi++)
		{
			((*itrpoi).second).getAllDataByReference(name, latitude, longitude,
					type, description);
			m_poiFile << name << ";" << latitude << ";" << longitude << ";"
					<< type << ";" << description << endl;
				}
		}
	else
	{
		cout<<"error:cannot create poifile!"<<endl;
		return false;
	}
	m_poiFile.close();
	return true;
}

bool CRPersistentStorage::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode)
{

	string format_CSV="";
	//hold value of keyword
	string value_key="";
	int next_line=0;
	int name_flag=0;
	int lati_flag=0;
	int longi_flag=0;
	int enum_flag=0;
	int desc_flag=0;
	string point_name="";
	double point_latitude;
	double point_longitude;
	ifstream CSV_file_wp,CSV_file_poi;
	CSV_file_wp.open("germany-wp.txt");
	CSV_file_poi.open("germany-poi.txt");

	/*
	 * CWaypoint CSV
	 */
	map<string, CWaypoint> map_wp = waypointDb.getMap();
	if (CSV_file_wp.is_open())
	{
		if (mode == REPLACE)
		{
			map_wp.clear();
			waypointDb.setMap(map_wp);
		}

		while (!CSV_file_wp.eof())
		{
			getline(CSV_file_wp, format_CSV);
			size_t pos = format_CSV.find(';');
			if (pos == std::string::npos)
			{
				cerr << "error:no semicolon found in line" << ++next_line
						<< endl;
				//return false;
			}
			else
			{
				value_key = format_CSV.substr(0, pos);
				if (value_key.empty() != true)
				{
					for (unsigned i = 0; i < value_key.length(); i++)
					{
						if (!((value_key[i] >= 'a' && value_key[i] <= 'z')
								|| (value_key[i] >= 'A' && value_key[i] <= 'Z')
								|| value_key[i] == ' '))
						{
							cerr << "error:incorrect name format in line "
									<< next_line << " for the keyword "
									<< value_key << endl;
							//return true;
						}
						name_flag = 1;
						point_name = value_key;
					}
				}
				else
				{
					cerr << "err:no characters in the " << value_key << endl;
					//return false;
				}
				format_CSV = format_CSV.substr(pos + 1); //check in this point
				pos = format_CSV.find(';');
				if (pos == std::string::npos)
				{
					cerr << "error at line " << next_line
							<< "error in csv text format " << format_CSV
							<< endl;
					//return true;
				}
				else
				{
					value_key = format_CSV.substr(0, pos); // holds the latitude
					if (processLatLong(value_key))
					{
						lati_flag = 1;
						point_latitude = strtod(value_key.c_str(), NULL);
					}
					else
					{
						cerr << "latitude line failure" << next_line << endl;
						//return false;
					}
					format_CSV = format_CSV.substr(pos + 1); //holds the longitude

					if (processLatLong(format_CSV))
					{
						point_longitude = strtod(format_CSV.c_str(), NULL);
						longi_flag = 1;
					}
					else
					{
						cerr << "longitude line failure " << next_line << endl;
						//return false;
					}
				}
			}
			if (name_flag == 1 && lati_flag == 1 && longi_flag == 1)
			{
				CWaypoint wayPoint;
				wayPoint.set(point_name, point_latitude, point_longitude);
				map<string, CWaypoint>::iterator itr;
				map_wp.insert(pair<string, CWaypoint>(point_name, wayPoint));
				waypointDb.addWaypoint(wayPoint);
				cout << "Waypoint added from File!! " << point_name << endl;
				cout << "Waypoint added count: " << map_wp.size() << endl;
				//for(itr=map_wp.begin();itr!=map_wp.end();itr++)
				//{
				//(*itr).second.print(MMSS);
				//}
				name_flag = 0; //set the flag to 0 for processing again.
				lati_flag = 0;
				longi_flag = 0;
				next_line = 0;
			}
			else
			{
				cerr << "error:check for the missing value in line: " << next_line
						<< endl;
				//return false;
			}

		}
		//return true;
	}
	else
	{
		cerr << "error:cannot open the waypoint File" << endl;
	}

	string point_description="";
	t_poi point_type=RESTAURANT;
	map<string, CPOI> map_poi=poiDb.getMap();

	if (CSV_file_poi.is_open())
	{
		if (mode == REPLACE)
		{
			map_poi.clear();
			poiDb.setMap(map_poi);
		}

		while (!CSV_file_poi.eof())
		{
			getline(CSV_file_poi, format_CSV);
			size_t pos = format_CSV.find(';');
			if (pos == std::string::npos)
			{
				cerr << "error:no semicolon found in line" << ++next_line
						<< endl;
				//return false;
			}
			else
			{
				value_key = format_CSV.substr(0, pos);
				if (value_key.empty() != true)
				{
					for (unsigned i = 0; i < value_key.length(); i++)
					{
						if (!((value_key[i] >= 'a' && value_key[i] <= 'z')
								|| (value_key[i] >= 'A' && value_key[i] <= 'Z')
								|| value_key[i] == ' '))
						{
							cerr << "error:incorrect name format in line "
									<< next_line << " for the keyword "
									<< value_key << endl;
							//return true;
						}
						name_flag = 1;
						point_name = value_key;
					}
				}
				else
				{
					cerr << "err:no characters in the " << value_key << endl;
					//return false;
				}
				format_CSV = format_CSV.substr(pos + 1); //check in this point
				pos = format_CSV.find(';');
				if (pos == std::string::npos)
				{
					cerr << "error at line " << next_line
							<< "error in csv text format " << format_CSV
							<< endl;
					//return true;
				}
				else
				{
					value_key = format_CSV.substr(0, pos); // holds the latitude
					if (processLatLong(value_key))
					{
						lati_flag = 1;
						point_latitude = strtod(value_key.c_str(), NULL);
					}
					else
					{
						cerr << "latitude line failure" << next_line << endl;
						//return false;
					}
				}
				format_CSV = format_CSV.substr(pos + 1); //holds the longitude
				pos = format_CSV.find(';');
				if (pos == std::string::npos)
				{
					cerr << "error at line " << next_line
							<< "error in csv text format " << format_CSV
							<< endl;
					//return true;
				}
				else
				{
					value_key = format_CSV.substr(0, pos);
					if (processLatLong(value_key))
					{
						point_longitude = strtod(value_key.c_str(), NULL);
						longi_flag = 1;
					}
					else
					{
						cerr << "longitude line failure at " << next_line
								<< endl;
						//return false;
					}
				}

				format_CSV = format_CSV.substr(pos + 1); //holds the type
				pos = format_CSV.find(';');
				if (pos == std::string::npos)
				{
					cerr << "error at line " << next_line
							<< "error in csv text format at " << format_CSV
							<< endl;
					//return true;
				}
				else
				{
					value_key = format_CSV.substr(0, pos);
					if (value_key == "0")
					{
						point_type = RESTAURANT;
						enum_flag = 1;
					}
					else if (value_key == "1")
					{
						point_type = SIGHTSEEING;
						enum_flag = 1;
					}

					else
					{
						cerr << "type line failure at" << next_line << endl;
						//return false;
					}

				}

				format_CSV = format_CSV.substr(pos + 1); //holds the description
				//process here description
				if (format_CSV.empty() != true)
					for (unsigned i = 0; i < format_CSV.length(); i++)
					{
						if (!((format_CSV[i] >= 'a' && format_CSV[i] <= 'z')
								|| (format_CSV[i] >= 'A' && format_CSV[i] <= 'Z')
								|| format_CSV[i] == ' '))
						{
							cerr << "error:incorrect name format in line "
									<< next_line << " for the keyword "
									<< format_CSV << endl;
							//return true;
						}
						desc_flag = 1;
						point_description = format_CSV;
					}

			}
			if (name_flag == 1 && lati_flag == 1 && longi_flag == 1
					&& desc_flag == 1 && enum_flag == 1)
			{
				CPOI cpoi;
				cpoi.getAllDataByReference(point_name, point_latitude,
						point_longitude, point_type, point_description);
				//cpoi(point_name,point_latitude,point_longitude);
				//cpoi.setType(point_type);
				map<string, CPOI>::iterator itr;
				map_poi.insert(pair<string, CPOI>(point_name, cpoi));
				poiDb.addPoi(cpoi);
				cout << "POI added from File!! " << point_name << endl;
				cout << "POI added count: " << map_poi.size() << endl;
//					for(itr=map_poi.begin();itr!=map_poi.end();itr++)
//					{
//					(*itr).second.print();
//					}
				name_flag = 0; //set the flag to 0 for processing again.
				lati_flag = 0;
				longi_flag = 0;
				next_line = 0;
				enum_flag = 0;
			}
			else
			{
				cerr << "error:check for the missing value " << next_line
						<< endl;
				//return false;
			}

		}
		//return true;
	}
	else
	{
		cerr << "error:cannot open the POI File" << endl;
	}

	CSV_file_wp.close();
	CSV_file_poi.close();
	bool wp_condition = false;
	bool poi_condition = false;
	if (CSV_file_wp.good())
	{
		wp_condition = true;
	}
	if (CSV_file_poi.good())
	{
		poi_condition = true;
	}

	if (wp_condition == true && poi_condition == true)
	{
		return true;
	}

return false;
}

bool CRPersistentStorage::processLatLong(string keywordValue)const
{
	bool true_False_Flag=0; //flag set only when value is processed properly
	int no_of_decimals=0; //to count the number of dots
	if(keywordValue.empty()!=true) // check for empty characters
	{
		for(unsigned i=0;i<keywordValue.length();i++) //check for other than 0-9,.,
		{  //check for 0-9, '.' and ','
			if (((keywordValue[i] >= '0' && keywordValue[i] <= '9')
					|| (keywordValue[i] == '.') || !(keywordValue[i] == ',')))
			{
				if (keywordValue[i] == '.')
				{
					no_of_decimals++; // for checking 2 dots
				}
			}
			else
			{   //if failed processing in the value.
				cerr<<"error: In the Keyword value "<<keywordValue<<endl;
				return false;
			}
		}
		if(no_of_decimals>1) // for more than 1 count.
		{
			no_of_decimals=0;//print the error for more than one count.
			cerr<<"There are more than 1 decimal in the "<<keywordValue<<endl;
			return false;
		}
		else
		{
			true_False_Flag=1;
		}
	}
	else
	{
		return false;
	}
	return true_False_Flag; //returns true for all the passed condition.

}
