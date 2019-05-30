// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>


#include <osgUtil/Optimizer>
#include <osg/PositionAttitudeTransform>
#include <osg/Switch>
#include <osg/MatrixTransform>
#include <osg/LineWidth>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>
#include "South.h"
#include <osg/Math>
#include <osg/NodeCallback>
#include <fstream>
#include <osgParticle/PrecipitationEffect>
#include "Condit.h"
#include <osgGA/FlightManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgDB/WriteFile>
#include <osg/LOD>
#include <osgDB/ReaderWriter>
#include <osgDB/Registry>
#include <osgGA/TrackballManipulator>
#include <osgSim/Impostor>
#include <osg/Depth>
#include <osgText/Text>

#include <osgUtil/Optimizer>
#include <osg/Material>
#include <osg/BlendFunc>
#include <osg/Projection>
#include <osg/io_utils>
#include <sstream>


class CPictureHolder2 :public osgGA::GUIEventAdapter
{
public:
	CPictureHolder2(osgText::Text* updateText):_updateText(updateText)
	{

	}
	~CPictureHolder2()
	{

	}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter & aa)
	{
		switch (ea.getEventType())
		{
		case (osgGA::GUIEventAdapter::FRAME):
			{
				osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
				viewer->getCamera()->getViewMatrixAsLookAt(position, center, up);
				if (viewer)
				{
					pick(viewer, ea);
				}

				return false;
			}

			break;
		default:
			return false;
			break;
		}

	}


	virtual void pick(osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter & ea)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;
		std::string gdlist = "";
		std::ostringstream os;
		os<< "X:->" << position[0] << "Y:->" << position[1] << "Z:" << position[2];
		gdlist += os.str();

		setLabel(gdlist);

	}

	void setLabel(const std::string& name)
	{
		if(_updateText.get())
		{

			_updateText->setText(name);
		}
	}

private:
	osg::Vec3 position;
	osg::Vec3 center;
	osg::Vec3 up;
	osg::ref_ptr<osgText::Text> _updateText;

};

class CreateHUD2
{
public:
	CreateHUD2()
	{
	
	}
	~CreateHUD2()
	{

	}

	osg::Node* createHUD(osgText::Text* updateText)
	{
		osg::Camera* hudCamera = new osg::Camera;
		hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		hudCamera->setProjectionMatrixAsOrtho2D(0,1280, 0,1024);
		hudCamera->setViewMatrix(osg::Matrix::identity());
		hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
		hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

		std::string timesFont("fonts/arial.ttf");
		osg::Vec3 position(0.f, 0.f, 0.f);

		{
			osg::Geode* geode = new osg::Geode();
			osg::StateSet* stateset = geode->getOrCreateStateSet();
			stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
			stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			geode->setName("The text label");
			geode->addDrawable(updateText);
			hudCamera->addChild( geode);
			updateText->setCharacterSize(20.0f);
			updateText->setFont(timesFont);
			updateText->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			updateText->setText("");
			updateText->setPosition(position);
			updateText->setDataVariance(osg::Object::DYNAMIC);
		}
		return hudCamera;
	}


private:
	osg::ref_ptr<osg::GraphicsContext::Traits> traits;


};

class CPickHandler:public osgGA::GUIEventHandler
{
public:
	CPickHandler(osgViewer::Viewer* viewer):mViewer(viewer){}

	virtual bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter& aa)
	{
/*		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if(!viewer)
		{
			return false;
		}
*/
		switch(ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
/*				if(ea.getKey() == 0xFF51)
				{
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
				}
				if(ea.getKey() == 0xFF53)
				{
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
				}
	*/		}
			break;
		case osgGA::GUIEventAdapter::PUSH:
			{
				if(ea.getButton() ==  1)
				{
					Pick(ea.getX(), ea.getY());
					return true;
				}

/*				if(ea.getButton() == 4)
				{
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
				}
*/			}
			break;
		case osgGA::GUIEventAdapter::DOUBLECLICK:
			{
/*				if(ea.getButton() == 1)
				{
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
				}
	*/		}
			break;
		default:

			break;

		}



		return false;
	}
private:
	void Pick(float x, float y)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;
		if(mViewer->computeIntersections(x, y, intersections))
		{
			osgUtil::LineSegmentIntersector::Intersections::iterator hitr;
			for( hitr = intersections.begin();hitr != intersections.end(); ++hitr);
			{
				if(! hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty()))
				{
					osg::NodePath  np = hitr->nodePath;
					for(int i = np.size()-1; i>=0; i--)
					{
						osgFX::Scribe *sc = dynamic_cast<osgFX::Scribe *>(np[i]);
						if(sc != NULL)
						{
							if(sc->getNodeMask() != 0)
							{
								sc->setNodeMask(0);
							}
						}
					}
				}
			}

		}

	}


	osgViewer::Viewer* mViewer;
};
class UseEventHandler:public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter& aa)
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if(!viewer)
		{
			return false;
		}

		switch(ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
				if(ea.getKey() == 0xFF51)
				{
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
				}
				if(ea.getKey() == 0xFF53)
				{
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
				}
			}
			break;
		case osgGA::GUIEventAdapter::PUSH:
			{
				if(ea.getButton() == 4)
				{
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
				}
			}
			break;
		case osgGA::GUIEventAdapter::DOUBLECLICK:
			{
				if(ea.getButton() == 1)
				{
					viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
					viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
				}
			}
			break;
		default:

			break;

		}



		return false;
	}
};

osg::ref_ptr<osg::Node> creteShape()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	float radus = 0.08f;

	float height = 0.1f;
	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);

	geode->addDrawable(new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radus), hints));
	geode->addDrawable(new osg::ShapeDrawable( new osg::Box(osg::Vec3(0.2f, 0.0f, 0.0f), 2* radus), hints));
	geode->addDrawable(new osg::ShapeDrawable( new osg::Cone(osg::Vec3(0.4f, 0.0f, 0.0f), radus, height), hints));
	geode->addDrawable(new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(0.6f, 0.0f, 0.0f), radus, height), hints));
	geode->addDrawable(new osg::ShapeDrawable( new osg::Capsule(osg::Vec3(0.8f, 0.0f, 0.0f), radus, height), hints));


	return geode.get();

}


osg::ref_ptr<osg::Node> createQuad()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));

	geom->addPrimitiveSet(		
		new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());

	return geode.get();

}


osg::ref_ptr<osg::Node> createLine()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::LineWidth> lineSize = new osg::LineWidth;
	lineSize->setWidth(10.0);
	geom->getOrCreateStateSet()->setAttributeAndModes(lineSize.get(), osg::StateAttribute::ON);



	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));

	geom->addPrimitiveSet(		
		new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());

	return geode.get();
}


osg::AnimationPath* createAnimationPath(const osg::Vec3& center, float radius, double looptime)
{
	osg::AnimationPath* animationPath = new osg::AnimationPath;
	animationPath->setLoopMode(osg::AnimationPath::LOOP);
	int unmSamples = 40;
	float yaw = 0.0f;
	float yaw_delta = 2.0f* osg::PI/((float)unmSamples-1.0f);
	float roll = osg::inDegrees(30.0f);

	double time = 0.0f;
	double time_delta = looptime/(double)unmSamples;
	for(int i=0; i< unmSamples; i++)
	{
		osg::Vec3 position(0,0,0);
		osg::Quat rotation(osg::Quat(roll, osg::Vec3(0.0, 1.0, 0.0))* 
			osg::Quat(-(yaw+osg::inDegrees(90.0f)), osg::Vec3(0.0, 0.0, 1.0)));
		animationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation));
		yaw += yaw_delta;
		time += time_delta;
	}

	return animationPath;
}
osg::Node* createMovingModel(osg::Group* root,const osg::Vec3& center, float radius)
{
	osg::Group* model = new osg::Group;
	float animationLength = 10.0f;
	osg::AnimationPath* animationPath = createAnimationPath(center, radius, animationLength);
	osg::Node* fountain = osgDB::readNodeFile("fountain.osgt");
	//fountain->asGroup()->getChild(0)->setNodeMask(0);

	if(fountain)
	{
		osg::PositionAttitudeTransform* xform = new osg::PositionAttitudeTransform;
		xform->setUpdateCallback(new osg::AnimationPathCallback(animationPath, 0.0, 1.0));
		xform->addChild(fountain);
		model->addChild(xform);
	}



	return  model;
}

osg::Node* createModel()
{
	osg::Group* root = new osg::Group;
	osg::Vec3 center(0.0f, 0.0f, 0.0f);
	float radius = 1.0f;

	osg::Node* movingModel = createMovingModel(root, center, radius*0.8f);
	root->addChild( movingModel );
	return root;
}

class MyTransformCallback:public osg::NodeCallback
{
public:
	MyTransformCallback(float angularVelocity)
	{
		m_angularVelocity = angularVelocity;

	}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);

		if(nv && (transform != NULL) && (nv->getFrameStamp() != NULL))
		{
			double time = nv->getFrameStamp()->getReferenceTime();
			transform->setMatrix(osg::Matrix::translate(0.0f, 1.0f+cosf(time*m_angularVelocity), 0.0f));
			traverse(node, nv);
		}
	}
private:
	float	m_angularVelocity;

};
class VertexExtractor: public osg::NodeVisitor
{
public:
	VertexExtractor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		extracted_verts = new osg::Vec3Array;
	}
	void apply(osg::Geode & geode)
	{
		for(unsigned int i=0; i< geode.getNumDrawables(); i++)
		{
			osg::Geometry* geom = dynamic_cast<osg::Geometry*> (geode.getDrawable(i));
			if(!geom)
			{
				continue;
			}

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
			if(!verts)
			{
				continue;
			}

			extracted_verts->insert(extracted_verts->end(), verts->begin(), verts->end());

		}
	}
	osg::ref_ptr<osg::Vec3Array> getextracted_verts()
	{
	
		return extracted_verts.get();
	}
private:
	osg::ref_ptr<osg::Vec3Array> extracted_verts;
};


void CreateCamera(osgViewer::Viewer &viewer)
{
	osg::GraphicsContext::WindowingSystemInterface* wsi =
		osg::GraphicsContext::getWindowingSystemInterface();

	unsigned int width, height;
	wsi->getScreenResolution( osg::GraphicsContext::ScreenIdentifier(0),width,height);

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 0;
	traits->y = 0;
	traits->width = width;
	traits->height = height;

	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	gc->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.6f, 1.0f));
	gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	osg::ref_ptr<osg::Camera> cameramaster = new osg::Camera;
	cameramaster->setGraphicsContext(gc.get());
	cameramaster->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
	viewer.addSlave(cameramaster.get());

	double ascpectRatioScale = 1.0;
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;

	camera->setGraphicsContext(gc.get());
	camera->setViewport(new osg::Viewport(0,0, width/4, height/4));
	GLenum buffer = traits->doubleBuffer?GL_BACK:GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);

	viewer.addSlave(camera.get(), osg::Matrixd(), osg::Matrixd::rotate(osg::DegreesToRadians(10.0), 0.0,1.0,0.0));


	//double ascpectRatioScale = 1.0;
	osg::ref_ptr<osg::Camera> camera1 = new osg::Camera;

	camera1->setGraphicsContext(gc.get());
	camera1->setViewport(new osg::Viewport(traits->width/4,0, traits->width/4, traits->height/4));
	GLenum buffer1 = traits->doubleBuffer?GL_BACK:GL_FRONT;
	camera1->setDrawBuffer(buffer1);
	camera1->setReadBuffer(buffer1);

	viewer.addSlave(camera1.get(), osg::Matrixd(), osg::Matrixd::rotate(osg::DegreesToRadians(-50.0), 0.0,1.0,0.0));


	//double ascpectRatioScale = 1.0;
	osg::ref_ptr<osg::Camera> camera2 = new osg::Camera;

	camera2->setGraphicsContext(gc.get());
	camera2->setViewport(new osg::Viewport((traits->width/4)*2-1,0, traits->width/4, traits->height/4));
	GLenum buffer2 = traits->doubleBuffer?GL_BACK:GL_FRONT;
	camera2->setDrawBuffer(buffer2);
	camera2->setReadBuffer(buffer2);

	viewer.addSlave(camera.get(), osg::Matrixd(), osg::Matrixd::rotate(osg::DegreesToRadians(120.0), 0.0,1.0,0.0));

	//double ascpectRatioScale = 1.0;
	osg::ref_ptr<osg::Camera> camera3 = new osg::Camera;

	camera3->setGraphicsContext(gc.get());
	camera3->setViewport(new osg::Viewport((traits->width/4)*3-2,0, traits->width/4, traits->height/4));
	GLenum buffer3 = traits->doubleBuffer?GL_BACK:GL_FRONT;
	camera3->setDrawBuffer(buffer3);
	camera3->setReadBuffer(buffer3);

	viewer.addSlave(camera.get(), osg::Matrixd(), osg::Matrixd::rotate(osg::DegreesToRadians(110.0), 0.0,1.0,0.0));
/*
	double ascpectRatioScale = 1.0;
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;

	camera->setGraphicsContext(gc.get());
	camera->setViewport(new osg::Viewport(0,0, width/4, height/4));
	GLenum buffer = traits->doubleBuffer?GL_BACK:GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);

	viewer.addSlave(camera.get(), osg::Matrixd(), osg::Matrixd::rotate(osg::DegreesToRadians(180.0), 0.0,1.0,0.0));
*/
}

void multipleWindowMultipleCameras(osgViewer::Viewer& viewer, bool multipleScreens)
{
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	unsigned int width, height;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);

	unsigned int numCameras = 6;

	double ascpecRatioScale = (double)numCameras;
	double translate_x = double(numCameras) -1;
	for(unsigned int i=0; i< numCameras; i++, translate_x -= 2.0)
	{
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		traits->screenNum = multipleScreens? i/3:0;
		traits->x = (i*width)/numCameras;
		traits->y =  0;

		traits->width = width/numCameras-1;
		traits->height = height;
		traits->windowDecoration = true;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext( traits.get());
		osg::ref_ptr<osg::Camera> camera = new osg::Camera;
		camera->setGraphicsContext(gc.get());
		camera->setViewport(new osg::Viewport(0,0,width/numCameras, height));
		GLenum buffer = traits->doubleBuffer? GL_BACK:GL_FRONT;
		camera->setDrawBuffer(buffer);
		camera->setReadBuffer(buffer);

		viewer.addSlave(camera.get(), osg::Matrix::scale(ascpecRatioScale, 1.0, 1.0)* 
			osg::Matrix::translate(translate_x, 0.0, 0.0), osg::Matrix());


	}
}

osg::Node* createHUD()
{
	osg::Geode* geode = new osg::Geode();
	std::string arial("fonts/arial.ttf");
	osg::StateSet* stateset = geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	osg::Vec3 position(150.f, 500.f,0.f);
	osgText::Text* text = new osgText::Text;
	geode->addDrawable(text);
	text->setFont(arial);

	text->setPosition( position);
	text->setText("OSG China");
	osg::Camera* camera = new osg::Camera;
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0,1024,0,768));
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	camera->setViewMatrix(osg::Matrix::identity());
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->addChild(geode);

	return camera;


}

int _tmain(int argc, _TCHAR* argv[])
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root  = new osg::Group();
	//osg::ArgumentParsera(&argc, argv);



	/*viewer.setSceneData( osgDB::readNodeFile("glider.osg"));
	
	
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	viewer.addEventHandler(new osgViewer::StatsHandler);
	{

	
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keySwitchManipulator =
		new osgGA::KeySwitchMatrixManipulator;
	keySwitchManipulator->addMatrixManipulator('1', "trackball", new osgGA::TrackballManipulator());
	keySwitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
	keySwitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
	keySwitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());


	viewer.setCameraManipulator(keySwitchManipulator.get());
	}
	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
	*/

	//osg::Switch* sw = new osg::Switch();
	//root->addChild(sw);


	//osg::Node* glider = osgDB::readNodeFile("glider.osg");
	//glider->asGroup()->addChild(osgDB::readNodeFile("cessna.osg"));

	//sw->addChild(glider,true);
	//osg::PositionAttitudeTransform* cowXForm =
	//	new osg::PositionAttitudeTransform();
	//cowXForm->setPosition( osg::Vec3(10, 0, 0));
	//cowXForm->addChild(osgDB::readNodeFile("cow.osg"));
	//cowXForm->setNodeMask(0x0);


	//sw->addChild(cowXForm);

	/*
	osg::Node* glider = osgDB::readNodeFile("glider.osg");

	root->addChild(glider);

	osg::ref_ptr<osg::MatrixTransform> trans =
		new osg::MatrixTransform;
	trans->setMatrix(osg::Matrix::translate(0, 0, 2));
	trans->addChild(glider);
	root->addChild(trans);

	osg::ref_ptr<osg::MatrixTransform> scale =
		new osg::MatrixTransform;
	scale->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5) * osg::Matrix::translate(0, 0, -5));
	scale->addChild(glider);
	root->addChild(scale);

	osg::ref_ptr<osg::MatrixTransform> rot =
		new osg::MatrixTransform;
	rot->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0),1, 0, 0)* osg::Matrix::scale(0.5, 0.5, 0.5) * osg::Matrix::translate(4, 0, -2));
	rot->addChild(glider);
	root->addChild(rot);
	*/


	//root->addChild(creteShape().get());

	//root->addChild();

	//osg::ref_ptr<osg::MatrixTransform> trans =
	//	new osg::MatrixTransform;
	//trans->setMatrix(osg::Matrix::translate(0, 0, 5));
	//trans->addChild(osgDB::readNodeFile("cow.osg"));
	//root->addChild(trans);
	//root->addChild(osgDB::readNodeFile("glider.osg"));


	//osg::ref_ptr<osgFX::Scribe> sc = new osgFX::Scribe();
	//sc->addChild(osgDB::readNodeFile("glider.osg"));
	//root->addChild(sc.get());

	//viewer.setSceneData(root.get());
	//viewer.addEventHandler(new CPickHandler(&viewer));

	//viewer.setSceneData(osgDB::readNodeFile("Model/jiaoc26.ive"));
	//osg::ref_ptr<osgGA::AnimationPathManipulator> amp = new osgGA::AnimationPathManipulator("saved_animation.path");
	//viewer.setCameraManipulator(amp.get());
	//viewer.setCameraManipulator( new CSouth() );

	//osg::Node* model = createModel();
	//viewer.setSceneData(model);
	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	//osg::Node* node = osgDB::readNodeFile("glider.osg");
	//osg::MatrixTransform* transform = new osg::MatrixTransform();
	//transform->setUpdateCallback(new MyTransformCallback(10.0f));
	//transform->addChild(node);
	//root->addChild(transform);
	//viewer.setSceneData(root);
	//osg::Node* rootNode = osgDB::readNodeFile("glider.osg");
	//VertexExtractor ivea;
	//rootNode->accept(ivea);
	//viewer.setSceneData(rootNode);



	//viewer.realize();
	//std::ofstream out("test.vertexs");
	//int size_t = ivea.getextracted_verts().get()->size();
	//std::vector<osg::Vec3>::iterator iter = ivea.getextracted_verts().get()->begin();
	//for(int i=0; i<size_t; i++)
	//{
	//	out << iter->x()<< " " << iter->y() << " "<< iter->z() << std::endl;
	//	iter++;
	//}

	//std::cout<<"Over"<< std::endl;
	//osgViewer::Viewer viewer;
	//osg::ref_ptr<osgParticle::PrecipitationEffect> precipitationEffect = 
	//	new osgParticle::PrecipitationEffect;
	//precipitationEffect->snow(0.5);

	//precipitationEffect->setParticleColor(osg::Vec4(1,1,1,1));
	//precipitationEffect->setWind(osg::Vec3(5,0,0));

	//root->addChild(precipitationEffect.get());
	//osg::Node* ceep = osgDB::readNodeFile("Model/jiaoc002.ive");
	//root->addChild(ceep);

	//CreateCamera(viewer);
	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	//viewer.setSceneData(osgDB::readNodeFile("Model/jiaoc002.ive"));

	//Conduit od;
	//od.setm_VecPostion(osg::Vec3(0,0,0));
	//root->addChild( od.CreateConduit(root));

	//viewer.setSceneData(root);
	//multipleWindowMultipleCameras(viewer, false);
	//viewer.setSceneData(osgDB::readNodeFile("glider.osg"));
	//osg::Node* node = osgDB::readNodeFile("fountain.osgt");
	//node->asGroup()->getChild(0)->setNodeMask(0);
	//viewer.setSceneData(node);
	//osg::LOD* lod = new osg::LOD;
	//lod->addChild(node, 0, 3000);
	//viewer.setSceneData(lod);
	//osgDB::writeNodeFile(*(viewer.getSceneData()), "free.osg", osgDB::Registry::instance()->getOptions());
	//osgSim::Impostor *sim = new osgSim::Impostor;
	//sim->addChild(node, 0, 3000);
	//sim->setImpostorThreshold(1000);
	//root->addChild(sim);
	//viewer.setSceneData(root);

	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("Model/jiaoc002.ive");
	if(scene.valid())
	{
		root->addChild(scene.get());
	}

	//CreateHUD2* hub2 = new CreateHUD2();

	//CPictureHolder2* hol = new CPictureHolder2();


	//hubca = hub2->createHUD(hub2->traits);
	//root->addChild(hubca);
	viewer.setSceneData(root.get());

	viewer.realize();

	viewer.run();

	return 0;
}

