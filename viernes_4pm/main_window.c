#include <dirent.h>
#include <stdlib.h> 
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <gst/gst.h>

///////////////////////////C.I.////////////////////////////////////

int RW = 0;
int mp = 0;
int mv = 0;
int SW = 0;



/////////////////////////MainWindow/////////////////////////////////

GtkBuilder *builder;
GtkWidget  *main_window;
GError     *error = NULL;
int volume=5;


////////////////////////////Radio///////////////////////////////////

GtkWidget *radio_window;
int fav_stations[20];
int fav_index=0;
int actual_index=0;

////////////////////////////Mp3///////////////////////////////////


GtkWidget *list_window;
GtkWidget *mp3_window;
char* select_song;

char* songs[100];
int song_index=0;
int play_song_index=0;


DIR *dir;
struct dirent *ent;

////////////////////////////Mp4///////////////////////////////////

GtkWidget *mp4_list_window;
GtkWidget *mp4_window;

char* movies[100];
int movie_index=0;
int play_movie_index=0;

DIR *mp4_dir;
struct dirent *mp4_ent;

//////////////////////Video////////////////////////////////////////



////////////////////////////Settings///////////////////////////////////

GtkWidget *settings_window;

////////////////////////////HEADER///////////////////////////////////


void list_init();
void radio_init();
void mp3_init();
void mp4_init();
void mp4_list_init();
void settings_init();
void music_play_init( int argc, char *argv[]);


///////////////////////////////////////////////////////////////////


void on_window_destroy(GtkObject *object, gpointer user_data)
{
   // gtk_main_quit ();
}

void on_radio_button_window_clicked(GtkButton *radio_button_window)
{// HIDE main_window and show radio_window widget
			
			if(RW==0){
			
				radio_init();
				RW=1;

			}

			gtk_widget_hide (main_window);
			gtk_widget_show(radio_window);

			
		}

void on_mp3_button_window_clicked(GtkButton *mp3_button_window)
{ // HIDE main_window and show mp3_window widget
			
			if(mp == 0){
				
				list_init();
				mp = 1;
			}

			
				gtk_widget_hide (main_window);
				gtk_widget_show_all(list_window);
			
			

		}

void on_mp4_button_window_clicked(GtkButton *mp4_button_window)
{ // HIDE main_window and show mp4_window widget

		
			if(mv==0){

				mp4_list_init();
				mv=1;

			}


			gtk_widget_hide (main_window);
			gtk_widget_show_all(mp4_list_window);

		}

void on_settings_button_window_clicked (GtkButton *settings_button_window)
{ // HIDE main_window and show settings_window widget

			 
			//if(SW==0){


				//settings_init();
				//Sw=1;

			//}


			//gtk_widget_hide (main_window);
			//gtk_widget_show (settings_window);

		}

///////////////////////////////////////////////////main///////////////////////////////////////////////////

int main (int argc, char *argv[])
{

	
    /* Init GTK+ */
    gtk_init( &argc, &argv );

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();

    /* Load UI from file.*/
    gtk_builder_add_from_file( builder, "main_window.glade", &error );

    /* Get main window pointer from UI */
    main_window = GTK_WIDGET( gtk_builder_get_object( builder, "main_window" ) );

    /* Connect signals */
    gtk_builder_connect_signals( builder, NULL );

    /* Destroy builder, since we don't need it anymore */
    g_object_unref( G_OBJECT( builder ) );


    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show( main_window );

    /* Start main loop */
    gtk_main();

    return( 0 );
}

/////////////////////////   LISTA   /////////////////////////////////////////

enum
{
  LIST_ITEM = 0,
  N_COLUMNS
};

static void
init_list(GtkWidget *list)
{

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("List Items",
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), 
      GTK_TREE_MODEL(store));

  g_object_unref(store);
}

static void
add_to_list(GtkWidget *list, const gchar *str)
{
  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}


void  on_changed(GtkWidget *widget, gpointer label) 
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  char *value;
	


  if (gtk_tree_selection_get_selected(
      GTK_TREE_SELECTION(widget), &model, &iter)) {

    gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
    gtk_label_set_text(GTK_LABEL(label), value);

	select_song =  gtk_label_get_text(GTK_LABEL(label));

    g_free(value);

	
  }}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// MUSICA!!!!! ////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void list_init(){

  GtkWidget *list;
  GtkWidget *vbox;
  GtkWidget *label; 
  GtkWidget *button;
  GtkTreeSelection *selection; 

  list_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(list_window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(list_window), 10);
  gtk_widget_set_size_request(list_window, 640, 480);
  gtk_window_set_title(GTK_WINDOW(list_window), "List View");

  list = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

  button = gtk_button_new_with_label("Play:");
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

	  g_signal_connect(button, "clicked", 
      		G_CALLBACK(mp3_init), NULL);

  label = gtk_label_new("");
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_end(GTK_BOX(vbox), label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(list_window), vbox);

  init_list(list);

   dir = opendir ("/home/nano/Desktop/test_music/");


   while ((ent = readdir (dir)) != NULL) {

 	if(ent->d_name != "." && ent->d_name != ".."  ){
	
   	add_to_list(list, ent->d_name); //cambiar ent->d_name por n para sacar info por id3

		songs[song_index]=ent->d_name;
		song_index=song_index+1;

		if(song_index>99){song_index=99;}

	}

       }

  closedir (dir);

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", 
      G_CALLBACK(on_changed), label);

 
}





/////////////////////////////////////Musica_second_window/////////////////////////////////////////////////////////////

	

	void mp3_init(){

		GtkBuilder* mp3_builder;

   	    mp3_builder = gtk_builder_new();
	    gtk_builder_add_from_file( mp3_builder, "mp3_solo.glade", &error );
	    mp3_window = GTK_WIDGET( gtk_builder_get_object( mp3_builder, "mp3_solo" ) );
	    gtk_builder_connect_signals(mp3_builder, NULL );
	    g_object_unref( G_OBJECT( mp3_builder ) );

		//play_song_index= k; song[k]==selectmusica;!!!!!!!!!!!!!!!!!!!!!!

	   	gtk_widget_show_all(mp3_window);
		gtk_widget_hide (list_window);
		music_play_init(0,NULL);


	}


	

	void mp3_back_song(GtkButton* back_button){ //Stop Music, destroy pipeline & init pipeline with new song -1

		//stop(songs[play_song_index]);	
	
		//if(play_song_index-1>0){
		//play(songs[play_song_index-1]);
		//}

		//else{
		//play_song_index=song_index;
		//play(songs[play_song_index]);
		//}
	
	}
	void mp3_next_song(GtkButton* next_button){

		//stop(songs[play_song_index]);	
	
		//if(play_song_index-1<song_index){
		//play(songs[play_song_index+1]);
		//}

		//else{
		//play_song_index=0;
		//play(songs[play_song_index]);
		//}

	}

	void mp3_play_button(GtkButton* play_song){

		//play(songs[play_song_index]);

	}

	void mp3_pause_button(GtkButton* pause_song){

		//pause_song(songs[play_song_index]);

	}

	void mp3_stop_button(GtkButton* stop_song){

		//stop(songs[play_song_index]);
	
	}

	void mp3_low_volume_button(GtkButton* low_volume){

		//if(volume>0){set_volume(volume-1);}	

	}

	void mp3_high_volume_button(GtkButton* high_volume){

		//if(volume<10){set_volume(volume+1);}	

	}

	void mp3_return(GtkButton* exit_button){

		//stop(songs[play_song_index]);

		gtk_widget_show_all(main_window); 
		gtk_widget_hide (mp3_window);
	
	} 

	void play(char* song){}
	//void pause_song(char* song){}
	void stop(char* song){}
	void set_volume(){}

/////////////////////////////////////////MUSICA/////////////////////////////////////////////////////////////////////


void set_song_index(){

	int a=0;

	while(a<99){

		if(select_song==songs[a]){
			
			play_song_index=a;
		}

		a=a+1;
	}

}

static void bus_call(GstBus *bus, GstMessage *msg, GMainLoop *mainloop )
{
    switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_EOS:
        g_print("EOS\n");
        g_main_loop_quit(mainloop);
        break;
    case GST_MESSAGE_ERROR:{
        gchar *debug;
        GError *error;
        gst_message_parse_error(msg, &error, &debug);
        g_free(debug);
        g_printerr("Error: %s\n", error->message);
        g_error_free(error);
        break;
    }
    case GST_MESSAGE_WARNING:{
        gchar *debug;
        GError *error;
        gst_message_parse_warning(msg, &error, &debug);
        g_printerr("WARNING: %s (%s)\n", error->message, (debug) ? debug : "no details");
        g_error_free(error);
        g_free(debug);
        break;
    }
    default:
        break;
    }
}

void music_play_init( int argc, char *argv[] )
{
    GstElement *playbin;
    GstElement *pipeline;
    GMainLoop *loop;
    GstBus *bus;

		

		char* name =  select_song;
		char* play = "file:///home/nano/Desktop/test_music/";
		char* name_with_extension;
		name_with_extension = malloc(strlen(name)+1+strlen(play)); 
		strcpy(name_with_extension, play); /* copy name into the new var */
		strcat(name_with_extension, name); /* add the extension */

		set_song_index();

    gst_init(&argc, &argv);
    pipeline = gst_pipeline_new( NULL );

    /* Create gstreamer elements */
    playbin = gst_element_factory_make( "playbin2", NULL );
    gst_bin_add( GST_BIN(pipeline), playbin );
    g_object_set( G_OBJECT(playbin), "uri", name_with_extension, NULL );

    /* bus callbacks */
    loop = g_main_loop_new( NULL, FALSE );
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline) );
    gst_bus_add_watch( bus, (GstBusFunc)bus_call, loop );
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    /* Iterate */
    g_main_loop_run(loop);


    /* Out of the main loop, clean up nicely */
    gst_element_set_state( pipeline, GST_STATE_NULL );
    gst_object_unref( GST_OBJECT(pipeline) );

   
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////RADIO//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void radio_init(){

	 GtkBuilder      *builder_radio;

    builder_radio = gtk_builder_new ();
    gtk_builder_add_from_file (builder_radio, "radio_window.glade", NULL);
    radio_window = GTK_WIDGET (gtk_builder_get_object (builder_radio, "radio_window"));
    gtk_builder_connect_signals (builder_radio, NULL);
    g_object_unref (G_OBJECT (builder_radio));

}


	void high_volume_button(GtkButton* volume_high){}
	void low_volume_button(GtkButton* volume_low){}


	void fav_button(GtkButton* save_station){

		//fav_stations[fav_index]=station;
		//fav_index=fav_index+1;
		//if(fav_index>19){fav_index=19;}
	
	}

	void next_button(GtkButton* forward_station){

		//station=fav_stations[actual_index+1];	
		//if(fav_index>19){actual_index=0;}
		//display(radio_station); //print gtktextBuffer
			

	}

	void back_button(GtkButton* back_station){


		//station=fav_stations[actual_index-1];	
		//if(fav_index<0){actual_index=19;}
		//display(radio_station);

	
	}

	void move_slider(){

		//station=movesliderint();
		//display(radio_station);	
	
	}


	void change_mode(GtkButton* mode){

		//if(mode_text=="AM"){mode_text="FM";}
		//else{mode_text="AM";}
		//display(mode_text);


		
	}

	void return_button(GtkButton* back){

		gtk_widget_show_all(main_window); 
		gtk_widget_hide (radio_window);

	}
		


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////MP4//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void mp4_list_init(){

  GtkWidget *mp4_list;
  GtkWidget *mp4_vbox;
  GtkWidget *mp4_label;
  GtkWidget *mp4_button;
  GtkTreeSelection *mp4_selection; 

  mp4_list_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(mp4_list_window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(mp4_list_window), 10);
  gtk_widget_set_size_request(mp4_list_window, 640, 480);
  gtk_window_set_title(GTK_WINDOW(mp4_list_window), "MP4 List View");

  mp4_list = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(mp4_list), FALSE);

  mp4_vbox = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(mp4_vbox), mp4_list, TRUE, TRUE, 5);

  mp4_button = gtk_button_new_with_label("Play:");
  gtk_box_pack_start(GTK_BOX(mp4_vbox), mp4_button, FALSE, FALSE, 5);

  g_signal_connect(mp4_button, "clicked", G_CALLBACK(mp4_init), NULL);

  mp4_label = gtk_label_new("");
  gtk_label_set_justify(GTK_LABEL(mp4_label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_end(GTK_BOX(mp4_vbox), mp4_label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(mp4_list_window), mp4_vbox);

  init_list(mp4_list);


  mp4_dir = opendir ("/home/nano/Desktop/test_mp4/");


   while ((mp4_ent = readdir (mp4_dir)) != NULL) {

   	add_to_list(mp4_list, mp4_ent->d_name); //cambiar ent->d_name por n para sacar info por id3
	movies[movie_index]=mp4_ent->d_name;
	
	movie_index=movie_index+1;

	if(movie_index>99){movie_index=99;}

       }

  closedir (mp4_dir);

 mp4_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(mp4_list));

  g_signal_connect(mp4_selection, "changed", G_CALLBACK(on_changed), mp4_label);

}

/////////////////////////////////////////////////Second_ Mp4///////////////////////////////////////////



void mp4_init(){

	GtkBuilder      *builder_mp4;

    builder_mp4 = gtk_builder_new ();
    gtk_builder_add_from_file (builder_mp4, "mp4_window.glade", NULL);
    mp4_window = GTK_WIDGET (gtk_builder_get_object (builder_mp4, "mp4_window"));
    gtk_builder_connect_signals (builder_mp4, NULL);
    g_object_unref (G_OBJECT (builder_mp4));

		 
		gtk_widget_hide (mp4_list_window);
		gtk_widget_show_all(mp4_window);


}

/////////////// Gstreamer MP4 Functions

	void play_movie_clicked(GtkButton* play_movie){
	
		//play_movie (movies[play_movie_index]);

	}

	void pause_movie_clicked(GtkButton* pause_movie){

		//pause_movie(movies[play_movie_index]);

	}

	void stop_movie_clicked(GtkButton* stop_movie){

		//stop_movie(movies[play_movie_index]);
	
	}

	void back_movie_clicked(GtkButton* back_movie){

		//stop_movie(movies[play_movie_index]);

		//if(play_movie_index>0){
		//play_movie(movies[play_movie_index-1]);}
		//else{play_movie_index=movie_index;
		//play_movie(movies[play_movie_index]); 

		//}

	}

	void next_movie_clicked(GtkButton* next_movie){

		//stop_movie(movies[play_movie_index]);
		//if(play_movie_index<movie_index){
		//play_movie(movies[play_movie_index+1]);}
		//else{play_movie_index=0;
		//play_movie(movies[play_movie_index]); 

		//}

	}

	void mp4_volumen_high_clicked(GtkButton* mp4_volumen_high){

		//if(volume<10){set_volume(volume+1);}	

	}
	void mp4_volumen_low_clicked(GtkButton* mp4_volumen_low){

		//if(volume>0){set_volume(volume-1);}	

	}

/////////

	void mp4_return_clicked(GtkButton* mp4_return){gtk_widget_hide(mp4_window); gtk_widget_show_all(main_window);}


////////////////////////////////////Video///////////////////////////////////////////////////////////////////////////////////

void play_pipe(GstElement *pipeline){

gst_element_set_state (pipeline, GST_STATE_PLAYING);

}

void pause_pipe(GstElement *pipeline){

gst_element_set_state (pipeline, GST_STATE_PAUSED); //GST_STATE_CHANGE_PLAYING_TO_PAUSED

}




void init_video(int argc, char *argv[]){

  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;
   
  /* Initialize GStreamer */
  gst_init (&argc, &argv);
   
  /* Build the pipeline */
  pipeline = gst_parse_launch ("playbin2 uri=file:///home/nano/Desktop/test_mp4/Pentatonix.mp4", NULL);
   
  /* Start playing */
  play_pipe(pipeline);
   
  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
   
 if (msg != NULL)
    gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);

}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
////////////////////////////////////////////////////Settings////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

void settings_init(){

    GtkBuilder      *builder_settings;

    builder_settings = gtk_builder_new ();
    gtk_builder_add_from_file (builder_settings, "settings_window.glade", NULL);
    settings_window = GTK_WIDGET (gtk_builder_get_object (builder_settings, "settings_window"));
    gtk_builder_connect_signals (builder_settings, NULL);
    g_object_unref (G_OBJECT (builder_settings));

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
