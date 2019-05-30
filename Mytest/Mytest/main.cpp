
#include "stdafx.h"

#include <osg/Geode>

#include <osgDB/WriteFile>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Image>
#include <osg/Material>
#include <osgText/Font>
#include <osgText/Text>
#include <osg/NodeCallback>
#include <osgGA/TrackballManipulator>
#include <osg/Camera>
#include <osg/Group>
//#include <osg/Util>

using std::endl;


class RotateCB: public osg::NodeCallback
{

public:
	RotateCB():_angle(0.f){}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::MatrixTransform * mtLeft = 
			dynamic_cast<osg::MatrixTransform*>( node);
		osg::Matrix mR,mT;
		mT.makeTranslate(-6.f, 0.f, 0.f);
		mR.makeRotate( _angle,osg::Vec3( 0.f, 0.f, 1.f));
		mtLeft->setMatrix(mR * mT);
		
		_angle += 0.01;

		traverse(node, nv);
	
	}

protected:
	double _angle;
};

osg::ref_ptr<osg::Node> createScene()
{
	osg::Node* cow = osgDB::readNodeFile("cow.osg");
	cow->setDataVariance(osg::Object::STATIC);

	osg::ref_ptr<osg::MatrixTransform> mtLeft = new osg::MatrixTransform;
	mtLeft->setName("Left Cow");

	mtLeft->setDataVariance(osg::Object::DYNAMIC);

	mtLeft->setUpdateCallback( new RotateCB);
	osg::Matrix m;
	m.makeTranslate( -6.f, 0.f, 0.f);
	mtLeft->setMatrix(m);
	mtLeft->addChild( cow );

	osg::ref_ptr<osg::MatrixTransform> mtRight = new osg::MatrixTransform;
	mtRight->setName("Right Cow");
	mtRight->setDataVariance(osg::Object::STATIC);
	m.makeTranslate(6.f, 0.f, 0.f);
	mtRight->setMatrix(m);
	mtRight->addChild( cow);





	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->setName( "Root Node");
	root->setDataVariance(osg::Object::STATIC);
	root->addChild( mtLeft.get() );
	
	
	root->addChild(mtRight.get() );

	return root.get();
}


/*
osg::ref_ptr<osg::Geode> createDrawable()
{
	osg::Geode* py


}
*/
osg::ref_ptr<osg::Node> createSceneGraph()
{
	osg::ref_ptr<osg::Group> root = new osg::Group;
	{
		osg::StateSet* state = root->getOrCreateStateSet();
		state->setMode(GL_LIGHTING,osg::StateAttribute::OFF | 
			osg::StateAttribute::PROTECTED);

	
	}
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	//osg::Geometry *pyramidGeometry = new osg::Geometry();
	//pyramidGeometry->setUpdateCallback(new TextureCoordUpdateCallback(0.01));
	//osg::Geode *pyramidGeode = new osg::Geode();
	//osg::Geometry *pyramidGeometry = new osg::Geometry;
	double r = 0.5;
	double h = 1.1;
	osg::Vec3 orginPt(0.5, 0.5, 0.0);
	osg::ref_ptr<osg::Geode> cylinderGeode = new osg::Geode;
	osg::ref_ptr<osg::Cylinder> geoCylinder = new osg::Cylinder( orginPt, r, h);
	osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable = new osg::ShapeDrawable( geoCylinder );
	//cylinderDrawable::apply(geoCylinder);
	cylinderDrawable->setColor( osg::Vec4( 1.0f, 1.0f, 0.0f, 1.0f));
	cylinderGeode->addDrawable( cylinderDrawable.get() );


	//geode->addDrawable( geoCylinder );
	//root->addChild(geode);
	
	osg::Matrix m;
	
	{
		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		m.makeTranslate(-2.f,0.f,2.f);
		mt->setMatrix(m);
		root->addChild( mt.get() );
		mt->addChild( cylinderGeode.get());
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
		geom->setTexCoordArray( 0, tc.get() );
		tc->push_back(osg::Vec2( 0.f, 0.f));
		tc->push_back(osg::Vec2( 1.f, 0.f));
		tc->push_back(osg::Vec2( 1.f, 1.f));
		tc->push_back(osg::Vec2( 0.f, 1.f));

		osg::StateSet* state = mt->getOrCreateStateSet();
		state->setMode( GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		state->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		state->setMode(GL_LIGHT0, osg::StateAttribute::ON);
		state->setMode(GL_LIGHT0, osg::StateAttribute::ON);


		osg::ref_ptr<osg::Light> light = new osg::Light;
		light->setAmbient( osg::Vec4(.5f, .5f, .5f, .5f));
		light->setDiffuse(osg::Vec4(.8f, .8f, .8f, 1.f));
		light->setSpecular(osg::Vec4(.8f, .8f, .8f,1.f));
		light->setPosition( osg::Vec4(0.f, 0.f, 0.f,0.f));
		light->setDirection( osg::Vec3(1.f, 1.f, 1.f));
		light->setSpotCutoff( 25.f );
		light->setLightNum(2);


		osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform;
		osg::Matrix m;
		m.makeTranslate( osg::Vec3( -3.f, 2.f, 5.f) );
		mt1->setMatrix( m );

		osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
		root->addChild( mt1.get() );
		mt1->addChild( ls.get() );
		ls->setLight( light.get() );


		osg::ref_ptr<osg::Material> mat = new osg::Material;
		mat->setDiffuse( osg::Material::FRONT, osg::Vec4( .2f, .9f, .9f, 1.f));
		mat->setSpecular( osg::Material::FRONT, osg::Vec4(1.f, 1.f, 1.f, 1.f));
		mat->setShininess( osg::Material::FRONT, 96.f);
		state->setAttribute( mat.get() );


		/*
		osg::ref_ptr<osg::Image> image = new osg::Image;
		image->setFileName("sun.tif");
		osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
		tex->setImage( image.get() );

		tex->setUnRefImageDataAfterApply( true);

		state->setTextureAttribute(0, tex.get() );
		state->setTextureMode( 1, GL_TEXTURE_2D, osg::StateAttribute::OFF);
		state->setTextureAttributeAndModes(0, tex);
		*/
	}

	{
		osg::ref_ptr<osg::MatrixTransform> mt =  new osg::MatrixTransform;
		m.makeTranslate(2.f, 0.f, 2.f);
		mt->setMatrix( m );
		root->addChild( mt.get() );
		mt->addChild( cylinderGeode.get() );
	
		osg::StateSet* state = mt->getOrCreateStateSet();
		osg::ShadeModel* sm = new osg::ShadeModel();
		sm->setMode( osg::ShadeModel::FLAT);
		state->setAttribute( sm);


		state->setMode( GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		state->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		state->setMode(GL_LIGHT0, osg::StateAttribute::ON);
		state->setMode(GL_LIGHT0, osg::StateAttribute::ON);


		osg::ref_ptr<osg::Light> light = new osg::Light;
		light->setAmbient( osg::Vec4(.5f, .5f, .5f, .5f));
		light->setDiffuse(osg::Vec4(.8f, .8f, .8f, 1.f));
		light->setSpecular(osg::Vec4(.8f, .8f, .8f,1.f));
		light->setPosition( osg::Vec4(0.f, 0.f, 0.f,0.f));
		light->setDirection( osg::Vec3(1.f, 1.f, 1.f));
		light->setSpotCutoff( 25.f );
		light->setLightNum(2);


		osg::ref_ptr<osg::Material> mat = new osg::Material;
		mat->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE);
		state->setAttribute( mat.get() );
	}

	{
		osg::ref_ptr< osg::MatrixTransform> mt = new osg::MatrixTransform;
		m.makeTranslate( -2.f, 0.f, -2.f);
		mt->setMatrix(m);
		root->addChild( mt.get() );
		mt->addChild( cylinderGeode.get() ); 
		osg::StateSet *state = mt->getOrCreateStateSet();
		osg::CullFace* cf = new osg::CullFace();
		state->setAttributeAndModes( cf );

		osg::ref_ptr<osgText::Font> font = osgText::readFontFile("cir.ttf");
		osg::ref_ptr<osgText::Text> text = new osgText::Text;
		text->setFont( font.get() );
		text->setText( "Display this message");
		//text->setPosition(osg::Vec3(10.f, 0.f, 1.f));
		text->setAxisAlignment( osgText::Text::SCREEN);
		text->setAlignment( osgText::Text::CENTER_TOP);
		text->setCharacterSize(5.0f);
		text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
		text->setFontResolution(128, 128);
		text->setColor( osg::Vec4(0.f, 0.f, 1.f, 1.f));

		cylinderGeode->addDrawable(text.get());	
	
	}

	{
		osg::ref_ptr< osg::MatrixTransform> mt = new osg::MatrixTransform;
		m.makeTranslate( 2.f, 0.f, -2.f);
		mt->setMatrix(m);
		root->addChild( mt.get() );
		mt->addChild( cylinderGeode.get() ); 

		osg::StateSet *state = mt->getOrCreateStateSet();
		//osg::CullFace* cf = new osg::CullFace();
		//state->setAttributeAndModes( cf );
		osg::PolygonMode* pm = new osg::PolygonMode(
			osg::PolygonMode::FRONT_AND_BACK,
			osg::PolygonMode::LINE
			
			);

		state->setAttributeAndModes(pm);
		osg::LineWidth *lw = new osg::LineWidth( 3.f);
		state->setAttribute( lw );


	}



	return root.get();
}

class PickHandler: public osgGA::GUIEventHandler
{
public:
	PickHandler():_mX(0.f),_mY(0.f){}
	bool handle( const osgGA::GUIEventAdapter & ea,
		osgGA::GUIActionAdapter & aa)
	{
		osgViewer::Viewer *viewer = 
			dynamic_cast<osgViewer::Viewer*>( &aa);
		if(!viewer)
		{
			return false;
		}
		switch( ea.getEventType() )
		{
		case osgGA::GUIEventAdapter::PUSH:

		case osgGA::GUIEventAdapter::MOVE:
			{
				_mX = ea.getX();
				_mY = ea.getY();

				return false;
			
			}
		case osgGA::GUIEventAdapter::RELEASE:
			{
			if(_mX == ea.getX() && _mY == ea.getY())
			{
				if(pick(ea.getXnormalized(), ea.getYnormalized(), viewer))
				{
					return true;
				}
			
			
			}
			
			return false;
			}
		default:
			return false;
		
		}




	
	}


protected:
	float _mX,_mY;
	bool pick( const double x, const double y, osgViewer::Viewer* viewer)
	{
		if(!viewer->getSceneData() )
		{
			return false;
		}



		double w(.05),h(.05);
		osgUtil::PolytopeIntersector * picker = 
			new osgUtil::PolytopeIntersector(
			osgUtil::Intersector::PROJECTION, x-w, y-h, x+w, y+h);
		osgUtil::IntersectionVisitor iv(picker);
		viewer->getCamera()->accept( iv );

		if(picker->containsIntersections())
		{
			osg::NodePath& nodePath =
				picker->getFirstIntersection().nodePath;
			unsigned int idx = nodePath.size();

/*			while(idx--)
			{
				osg::MatrixTransform *mt = 
					dynamic_cast<osg::MatrixTransform*>(nodePath[idx]);
				if(mt == NULL)
				{
					continue;
				}
				if(_selectedNode.valid())
				{
					_selectedNode->setUpdateCallback(NULL);
					_selectedNode = mt;
					_selectedNode->setUpdateCallback(new RotateCB);
					break;
				
				
				}
				if( !_selectedNode.valid())
				{
					osg::notify << "pick failed." << std::endl;
				}
			
			}
			*/
		/*else if(_selectedNode.vaild())
		{
			_selectedNode->setUpdateCallback( NULL);
			_selectedNode = NULL;
		
		}
		*/
		//return _selectedNode.valid();
		return true;
		}
	
	}
};






int _tmain(int argc, _TCHAR* argv[])
{


	osgViewer::Viewer viewer;
	viewer.setSceneData( createScene().get() );
	viewer.getCamera()->setClearColor( osg::Vec4( 1., 1.f, 1.f, 1.f));
	viewer.addEventHandler( new PickHandler);
	viewer.run();
/*	osg::ref_ptr<osg::Node> root = createSceneGraph();
	if( !root.valid() )
	{
		osg::notify(osg::FATAL)<< "Failed create" << endl;
	}


	bool result = osgDB::writeNodeFile( *(root.get()), "Simple.osg");
	if(!result)
	{
		osg::notify(osg::FATAL) << "Failed write" << endl;
	}

	osgViewer::Viewer viewer;
	viewer.setSceneData( osgDB::readNodeFile("Simple.osg"));
	//viewer.setUpViewInWindow(300, 100, 800, 600);
	viewer.getCamera()->setProjectionMatrixAsPerspective(40.f, 1.f, 1.f, 100.f);
	osg::Matrix trans;
	trans.makeTranslate( 0.f, 0.f, -12.f);
	double angle(0.f);

	viewer.getCamera()->setClearColor( osg::Vec4(0.f, 0.f, 0.f, 1.f));
	viewer.getCamera()->setClearMask( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	while(!viewer.done() )
	{
		osg::Matrix rot;
		rot.makeRotate( angle, osg::Vec3(1.f, 0.f, 0.f));
		angle += 0.01;
		viewer.getCamera()->setViewMatrix( rot *trans);
		viewer.frame();
	
	
	}

	return viewer.run();
*/
}