/*
 * CDatabaseTemplate.h
 *
 *  Created on: 17.01.2017
 *      Author: stbidula
 */

#ifndef CDATABASETEMPLATE_H_
#define CDATABASETEMPLATE_H_
//#include<map>
#include<iostream>
template<class T>
class CDatabaseTemplate{
private:
  	std::map<string, T> m_tmpMap;

public:
	  	void addData(T const& data);
	  	T* getPointerToName(string name);
	  	void tmpPrint();
	  	std::map<string, T> getTmpMap() const;
		void setTmpMap(std::map<string, T> maptype);
};

template<class T>
inline void CDatabaseTemplate<T>::addData(const T& data) {
//	CPOI* tempCast=NULL;
//	typename map<T,Z>::iterator itr=m_tmpMap.begin();
//	//typename interator it
//	tempCast=dynamic_cast<CPOI*>(*itr);
//					if(tempCast!=NULL)
//					{
//
//
//					}
//					else
//					{
//
//					}
	m_tmpMap.insert(pair<string, T> (data.getName(),data));

}


template<class T>
inline T* CDatabaseTemplate<T>::getPointerToName(string name)
{
	//iterator of map with key value Z and Class Type T
	typename std::map<string, T>::iterator tmp_itr;
	if(m_tmpMap.empty()==0)
			{
			for (tmp_itr = m_tmpMap.begin(); tmp_itr != m_tmpMap.end(); tmp_itr++)
						{
							//compare the incoming @param to the index of map
							if (tmp_itr->second.getName() == name)
							{
								//return the index if found
								return &(m_tmpMap.at(tmp_itr->first));
							}
						}

			}
			else
			{
			std::cout<<"error: Waypoint Database Empty!!"<<std::endl;
			}
return NULL;
}


template<class T>
inline void CDatabaseTemplate<T>::tmpPrint()
{
	typename std::map<string, T>::iterator tmp_itr;
		for (tmp_itr = m_tmpMap.begin(); tmp_itr != m_tmpMap.end(); tmp_itr++)
		{

			cout<<(tmp_itr->first)<<endl;
		}
}

template<class T>
inline std::map<string, T> CDatabaseTemplate<T>::getTmpMap() const
{
	return m_tmpMap;
}

template<class T>
inline void CDatabaseTemplate<T>::setTmpMap(map<string, T> maptype)
{
	m_tmpMap=maptype;
}

#endif /* CDATABASETEMPLATE_H_ */



