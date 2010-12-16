
#include <GL/gl.h>
#include <GL/glu.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>


#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/sound.h>

#include <iostream>

   using std::cout; using std::endl;
class SpritesExample
{
private:
         int sizex;
         int sizey;
	bool quit;

public:
      SpritesExample(int startx,int starty) : sizex(startx), sizey(starty){}
       void resize(CL_Rect &lol)
      {
         int x = lol.right- lol.left;
         int y = lol.bottom - lol.top;
         sizex = x;
         sizey = y;         
      }

	void run()
	{
 
		quit = false;

		CL_DisplayWindowDescription window_desc;
		window_desc.set_size(CL_Size(sizex, sizey), true);
		window_desc.set_title("Chess");
                window_desc.set_allow_resize(true);
		CL_DisplayWindow window(window_desc);

		CL_Slot slot_quit = window.sig_window_close().connect(this, &SpritesExample::on_window_close);
                window.func_window_resize().set(this, &SpritesExample::resize);

		CL_GraphicContext gc = window.get_gc();
		CL_InputDevice keyboard = window.get_ic().get_keyboard();

		CL_ResourceManager resources("resources.xml");

                CL_Image lol(gc,"Board",&resources);

               CEGUI::OpenGLRenderer & myRenderer = CEGUI::OpenGLRenderer::bootstrapSystem();

                 CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();

    CEGUI::DefaultWindow* root = (CEGUI::DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");

CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

   CEGUI::FrameWindow* wnd = (CEGUI::FrameWindow*)winMgr.createWindow("TaharezLook/FrameWindow", "Demo Window");

    root->addChildWindow(wnd);

    wnd->setPosition(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim( 0.25f)));
    wnd->setSize(CEGUI::UVector2(cegui_reldim(0.5f), cegui_reldim( 0.5f)));

    // now we set the maximum and minum sizes for the new window.  These are
    // specified using relative co-ordinates, but the important thing to note
    // is that these settings are aways relative to the display rather than the
    // parent window.
    //
    // here we set a maximum size for the FrameWindow which is equal to the size
    // of the display, and a minimum size of one tenth of the display.
    wnd->setMaxSize(CEGUI::UVector2(cegui_reldim(1.0f), cegui_reldim( 1.0f)));
    wnd->setMinSize(CEGUI::UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));

    // As a final step in the initialisation of our sample window, we set the window's
    // text to "Hello World!", so that this text will appear as the caption in the
    // FrameWindow's titlebar.
    wnd->setText("Hello World!");
                        CEGUI::System::getSingleton().renderGUI();
			window.flip();

         	while (!quit)
		{
			if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
				quit = true;


		        CL_Colorf red(155/255.0f, 60/255.0f, 68/255.0f);
		        //CL_Draw::fill(gc, CL_Rectf(0, sizey, sizex, 0), red);
                        //lol.draw(gc,CL_Rectf(0,sizey,sizex,0));
                        //CEGUI::System::getSingleton().renderGUI();

			//window.flip();
			CL_KeepAlive::process();
			CL_System::sleep(10);
		}
	}

	void draw_sunset(CL_GraphicContext &gc)
	{
		CL_Colorf red(155/255.0f, 60/255.0f, 68/255.0f);
		CL_Colorf yellow(255/255.0f, 234/255.0f, 117/255.0f);
		CL_Colorf blue(13/255.0f, 75/255.0f, 74/255.0f);
		CL_Colorf lightblue(16/255.0f, 91/255.0f, 90/255.0f);

		// Draw top of sunset
		CL_Gradient gradient1(CL_Colorf::black, red);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,0,640,160), gradient1);

		// Draw second part of sunset
		CL_Gradient gradient2(red, yellow);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,160,640,240), gradient2);

		// Draw the sun
		CL_Draw::circle(gc, CL_Pointf(320, 240), 15, CL_Colorf::white);

		// Draw the ground
		CL_Draw::fill(gc, CL_Rectf(0, 240, 640, 480), blue);

		// Draw some distance lines
		for(int y = 241, ydelta = 2; y < 480; y += ydelta, ydelta += ydelta)
		{
			CL_Draw::line(gc, 0, y, 640, y, lightblue);
		}
	}

	void on_window_close()
	{
		quit = true;
	}
   
      
};

int mymain(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;

		try
		{
			SpritesExample example(640,480);
			example.run();
		}
		catch(CL_Exception &exception)
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write_line("Error: " + exception.get_message_and_stack_trace());
			console.display_close_message();

			return -1;
		}

		return 0;
	}
CL_ClanApplication app(mymain);
