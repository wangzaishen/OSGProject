#pragma once

#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectionVisitor>
#include <osg/LineSegment>


class CSouth: public osgGA::CameraManipulator
{
public:
	CSouth(void);
	~CSouth();
	void setByMatrix(const osg::Matrixd& matrix);

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	void setByInverseMatrix(const osg::Matrixd& matrix);

	/** get the position of the manipulator as 4x4 Matrix.*/
	osg::Matrixd getMatrix()const;

	/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
	osg::Matrixd getInverseMatrix()const;

	void setPeng(bool peng);
	bool getPeng();
	void setFpeng();
	virtual void setNode(osg::Node*);
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
	void ChangePosition( osg::Vec3& delt);
	float getSpeed();
	void setSpeed(float sp);
	void SetPosition(osg::Vec3 &position);
	void SetPosition(double *);

	osg::Vec3 GetPosition();
	void computeHomePosition();
	void setAngle( float angle);
	float getAngle();

private:
	osg::ref_ptr<osg::Node>		m_node;
	unsigned int	m_nID;
	float			m_fMoveSpeed;
	osg::Vec3		m_vPosition;
	osg::Vec3		m_vRotation;
	bool			m_bLeftButtonDown;
	float			m_fpushX;
	bool			m_bPeng;
	float			m_fpushY;
	float			m_fAngle;



};