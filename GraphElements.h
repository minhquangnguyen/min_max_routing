///////////////////////////////////////////////////////////////////////////////
///  GraphElements.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 5/28/2010
///
///  $Id: GraphElements.h 65 2010-09-08 06:48:36Z yan.qi.asu $
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <iostream>
using namespace std;

template<class T>
class WeightGreater
{
public:
	// Determine priority.
	bool operator()(const T& a, const T& b) const
	{
		return a.Weight() > b.Weight();
	}

	bool operator()(const T* a, const T* b) const
	{
		return a->Weight() > b->Weight();
	}
};

template<class T>
class WeightLess
{
public:
	// Determine priority.
	bool operator()(const T& a, const T& b) const
	{
		return a.Weight() < b.Weight();
	}

	bool operator()(const T* a, const T* b) const
	{
		return a->Weight() < b->Weight();
	}
};

//////////////////////////////////////////////////////////////////////////
// A class for the object deletion
//////////////////////////////////////////////////////////////////////////
template<class T>
class DeleteFunc
{
public:
	void operator()(const T* it) const
	{
		delete it;
	}
};



/**************************************************************************
*  BaseVertex
*  <TODO: insert class description here>
*
*
*  @remarks <TODO: insert remarks here>
*
*  @author Yan Qi @date 6/6/2010
**************************************************************************/
class BaseVertex
{
	int m_nID;
	double m_dWeight;

public:

	int getID() const { return m_nID; }
	void setID(int ID_) { m_nID = ID_; }

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }
	
	/*BaseVertex operator=(BaseVertex &b)
	{
		this->m_nID = b.m_nID;
		this->m_dWeight = b.m_dWeight;
		return *this;
	}*/

	void PrintOut(std::ostream& out_stream)
	{
		out_stream << m_nID;
	}
};


/**************************************************************************
*  BasePath
*  <TODO: insert class description here>
*
*
*  @remarks <TODO: insert remarks here>
*
*  @author Yan Qi @date 6/6/2010
**************************************************************************/
class BasePath
{
//protected:
public:

	int m_nLength;
	double m_dWeight;
	std::vector<BaseVertex*> m_vtVertexList;
//public:

	BasePath(const std::vector<BaseVertex*>& vertex_list, double weight)
		:m_dWeight(weight)
	{
		m_vtVertexList.assign(vertex_list.begin(), vertex_list.end());
		m_nLength = m_vtVertexList.size();
	}
	
	BasePath(BasePath* p)
	{
		std::vector<BaseVertex*>::iterator it;
		it = p->m_vtVertexList.begin();
		m_vtVertexList.assign(it, p->m_vtVertexList.end());
		m_nLength = m_vtVertexList.size();
		m_dWeight = p->m_dWeight;
	}
	
	~BasePath(void){}

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }

	int length() { return m_nLength; }
	
	BasePath operator=(BasePath &b)
	{
		this->m_nLength = b.m_nLength;
		this->m_dWeight = b.m_dWeight;
		this->m_vtVertexList.assign(b.m_vtVertexList.begin(), b.m_vtVertexList.end());
		return *this;
	}

	BaseVertex* GetVertex(int i)
	{
		return m_vtVertexList.at(i);
	}

	bool SubPath(std::vector<BaseVertex*>& sub_path, BaseVertex* ending_vertex_pt)
	{

		for (std::vector<BaseVertex*>::const_iterator pos = m_vtVertexList.begin();
			pos != m_vtVertexList.end(); ++pos)
		{
			if (*pos != ending_vertex_pt)
			{
				sub_path.push_back(*pos);
			}
			else
			{
				//break;
				return true;
			}
		}
		return false;
	}

	// display the content
	void PrintOut(std::ostream& out_stream) const
	{
		out_stream << "Cost: " << m_dWeight << " Length: " << m_vtVertexList.size() << std::endl;
		for(std::vector<BaseVertex*>::const_iterator pos=m_vtVertexList.begin(); pos!=m_vtVertexList.end();++pos)
		{
			(*pos)->PrintOut(out_stream);
			out_stream << "->";
		}
		out_stream << std::endl <<  "*********************************************" << std::endl;
	}
};

typedef struct request
{
public:
	int source;
	int destination;
}
request;
