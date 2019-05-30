#pragma once
#include <osgViewer/Viewer>
#include <osg/LineSegment>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/IntersectionVisitor>
#include <osgGA/DriveManipulator>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osgUtil/Optimizer>
#include <osg/ShapeDrawable>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <math.h>
#include "Person.h"
#include <osgUtil/IntersectionVisitor>
#include "Robot.h"

class TravelManipulator :
	public osgGA::CameraManipulator
{
public:
	TravelManipulator(void);
	~TravelManipulator(void);

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByMatrix(const osg::Matrixd& matrix);

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);

	/** get the position of the manipulator as 4x4 Matrix.*/
	virtual osg::Matrixd getMatrix() const;

	/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
	virtual osg::Matrixd getInverseMatrix() const;
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);
	void setPerson(Person* perosn);
	//void setRobot(Robot* perosn);
	void setViewer(osgViewer::Viewer & viewer);
private:
	void		ChangePosition(osg::Vec3 & delta);

	float		getSpeed();
	void		setSpeed(float &sp);
	void		setPosition(osg::Vec3 &position );
	osg::Vec3	GetPosition();
	void KeyAction_i();
	void KeyAction_j();
	void KeyAction_l();

private:
	float	angle1;
	float	angle;
	float	move;
	float	scale;
	int		singal;

	//osg::ref_ptr<osgViewer::Viewer>	m_pHostViewer;
	float		m_fMoveSpeed;
	osg::Vec3	m_vPosition;
	osg::Vec3	m_vRotation;
	bool		m_bLeftButtonDown;
	float		m_fpushX;
	float		m_fpushY;
	float		m_fAngle;
	bool		m_bPeng;
	float		m_fMouseX;
	float		m_fMouseY;
	Person*		m_cPerson;
	//Robot*		m_cPerson;
	osgViewer::Viewer		m_pHostViewer;
};

