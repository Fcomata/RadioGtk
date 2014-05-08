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
int mp3=0;



/////////////////////////MainWindow/////////////////////////////////

GtkBuilder *builder;
GtkWidget  *main_window;
GError     *error = NULL;
double volume = 1.0;
GdkColor black;
GdkColor neon_green;



////////////////////////////Radio///////////////////////////////////

GtkWidget *radio_window;
int fav_stations[20];
int fav_index=0;
int actual_index=0;
int station_array[4];
int station_variable=1047;
int station_state;
int fav_station_save=0;
int fav_station_1;
int fav_station_2;

////////////////////////////Mp3///////////////////////////////////


GtkWidget *list_window;
GtkWidget *mp3_window;
char* select_song;
GtkWidget* song_label;
int song_index=0;
int play_song_index=0;
char* path = "file:///home/nano/Desktop/Empotrados/Interface_proto_1/app/test_music/";
DIR *dir;
struct dirent *ent[100];

DIR *dir2;


////////////////////////////Mp4///////////////////////////////////

GtkWidget *mp4_list_window;
GtkWidget *mp4_window;

char* movies[100];
int movie_index=0;
int play_movie_index=0;

DIR *mp4_dir;
struct dirent *mp4_ent;

//////////////////////musica gst////////////////////////////////////////

    GstElement *playbin;
    GstElement *pipeline;
    GMainLoop *loop;
    GstBus *bus;
///////////////////////////radio ////////////////////////////////

	GtkWidget* image_decimal;
	GtkWidget* image_unidad;
	GtkWidget* image_decena;
	GtkWidget* image_centena;
	GtkWidget* image_aof;
	GtkWidget* image_punto;
	GtkWidget* image_m;

	char* aof_text="FM";

////////////////////////////Settings///////////////////////////////////

GtkWidget *settings_window;

////////////////////////////HEADER///////////////////////////////////


void list_init();
void radio_init();
void mp3_init();
void mp3_build();
void mp4_init();
void mp4_list_init();
void settings_init();
void music_play_init( int argc, char *argv[], int state);
void init_video(int argc, char *argv[], char* movie);
void set_song_index();
char* function_alpha();
void set_image();


///////////////////////////////////////////////////////////////////


void on_window_destroy(GtkObject *object, gpointer user_data)
{
   // gtk_main_quit ();
}

void radio_button_window_clicked(GtkButton *radio_button_window)
{// HIDE main_window and show radio_window widget
			
			if(RW==0){
			
				radio_init();
				RW=1;

			}

			gtk_widget_hide (main_window);
			gtk_widget_show_all(radio_window);

			
		}

void mp3_button_window_clicked(GtkButton *mp3_button_window)
{ // HIDE main_window and show mp3_window widget
			
			if(mp == 0){
				
				list_init();
				mp = 1;
			}

			
				gtk_widget_hide (main_window);
				gtk_widget_show_all(list_window);
			
			

		}

void mp4_button_window_clicked(GtkButton *mp4_button_window)
{ // HIDE main_window and show mp4_window widget

		
			if(mv==0){

				mp4_list_init();
				mv=1;

			}


			gtk_widget_hide (main_window);
			gtk_widget_show_all(mp4_list_window);

		}

void settings_button_window_clicked (GtkButton *settings_button_window)
{ // HIDE main_window and show settings_window widget

			 
			//if(SW==0){


				//settings_init();
				//Sw=1;

			//}


			//gtk_widget_hide (main_window);
			//gtk_widget_show_all (settings_window);

		}

///////////////////////////////////////////////////main///////////////////////////////////////////////////

int main (int argc, char *argv[])
{

	GtkWidget* main_vbox;
	GtkWidget* main_hbox_1;
	GtkWidget* main_hbox_2;

	black.red=0;
	black.green=0;
	black.blue=0;

	neon_green.green= 65535;
	neon_green.blue=0;
	neon_green.red=0;

	GtkWidget* radio_button_window;
	GtkWidget* mp3_button_window;
	GtkWidget* mp4_button_window;
	GtkWidget* settings_button_window;

	 /* Init GTK+ */
   	gtk_init( &argc, &argv );
	
		//WINDOW
	  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	  gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	  gtk_widget_set_size_request(main_window, 640, 480);
	  gtk_window_set_decorated (GTK_WINDOW(main_window),FALSE);

		//Init Elements
		radio_button_window = gtk_button_new_with_label("Radio");
		mp3_button_window = gtk_button_new_with_label("MP3");
		mp4_button_window = gtk_button_new_with_label("MP4");
		settings_button_window = gtk_button_new_with_label("Settings");	

		//gtk_button_set_image (button_radio, GtkWidget *image);
	
   		//Containers

		main_vbox = gtk_vbox_new(FALSE, 0);
		main_hbox_1 = gtk_hbox_new(FALSE, 0);
		main_hbox_2 = gtk_hbox_new(FALSE, 0);

  		gtk_box_pack_start(GTK_BOX(main_vbox), main_hbox_1, TRUE, TRUE, 10);
  		gtk_box_pack_end(GTK_BOX(main_vbox), main_hbox_2, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(main_hbox_1), radio_button_window, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(main_hbox_1), mp3_button_window, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(main_hbox_2), mp4_button_window, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(main_hbox_2), settings_button_window, TRUE, TRUE, 10);

		gtk_container_add(GTK_CONTAINER(main_window), main_vbox);

	gtk_widget_modify_bg(main_window, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(GTK_WIDGET(radio_button_window), GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(GTK_WIDGET(mp3_button_window), GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(GTK_WIDGET(mp4_button_window), GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(GTK_WIDGET(settings_button_window), GTK_STATE_NORMAL, &black);

	gtk_widget_modify_bg(GTK_WIDGET(radio_button_window), GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(GTK_WIDGET(mp3_button_window), GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(GTK_WIDGET(mp4_button_window), GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(GTK_WIDGET(settings_button_window), GTK_STATE_PRELIGHT, &neon_green);

	//// CORREGIR TEXTO COLOR	
	gtk_widget_modify_text(GTK_WIDGET(radio_button_window), GTK_STATE_NORMAL, &neon_green);
	gtk_widget_modify_text(GTK_WIDGET(mp3_button_window), GTK_STATE_NORMAL, &neon_green);
	gtk_widget_modify_text(GTK_WIDGET(mp4_button_window), GTK_STATE_NORMAL, &neon_green);
	gtk_widget_modify_text(GTK_WIDGET(settings_button_window), GTK_STATE_NORMAL, &neon_green);

	gtk_window_set_decorated(GTK_WINDOW(main_window),FALSE);

		

    /* Connect signals */ ////////////////////////////////////////////////
 
	g_signal_connect(radio_button_window, "clicked", G_CALLBACK(radio_button_window_clicked), NULL);
	g_signal_connect(mp3_button_window, "clicked", G_CALLBACK(mp3_button_window_clicked), NULL);
	g_signal_connect(mp4_button_window, "clicked", G_CALLBACK(mp4_button_window_clicked), NULL);
	g_signal_connect(settings_button_window, "clicked", G_CALLBACK(settings_button_window_clicked), NULL);


    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show_all( main_window );

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

		g_print("%s", select_song);

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
  gtk_window_set_decorated (GTK_WINDOW(list_window),FALSE);

  list = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);


  vbox = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

  button = gtk_button_new_with_label("Play");
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

  g_signal_connect(button, "clicked", G_CALLBACK(mp3_init), NULL);

  label = gtk_label_new("");
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_end(GTK_BOX(vbox), label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(list_window), vbox);

  init_list(list);

   dir = opendir ("/home/nano/Desktop/Empotrados/Interface_proto_1/app/test_music/");

	

   while ((ent[song_index] = readdir (dir)) != NULL) {

	if (strcmp(ent[song_index]->d_name, ".") != 0 && strcmp(ent[song_index]->d_name, "..") != 0 ){

   		add_to_list(list, ent[song_index]->d_name); 

		song_index = song_index+1;

		if(song_index>99){song_index=99;}

		

		}

       }

  closedir (dir);

	
	gtk_widget_modify_bg(GTK_WIDGET(list_window), GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(GTK_WIDGET(button), GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(GTK_WIDGET(button), GTK_STATE_ACTIVE, &neon_green);


  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", 
      G_CALLBACK(on_changed), label);

 
}





/////////////////////////////////////Musica_second_window/////////////////////////////////////////////////////////////

	void mp3_init(){

		if(mp3==0){
			mp3_build();
			mp3=1;

		}

		else{
			gtk_widget_show_all(mp3_window);
			gtk_widget_hide (list_window);
			music_play_init(0,NULL,1);

		}

	}



	void mp3_back_song(GtkButton* back_button){ //Stop Music, destroy pipeline & init pipeline with new song -1

		if(play_song_index-1 > 0){

			play_song_index=play_song_index-1;
	
		}

		else{
			play_song_index=song_index-1;
			
		}

			select_song = ent[play_song_index]->d_name;

			g_print("%s \n",ent[play_song_index]->d_name);
			
		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		gst_element_set_state( pipeline, GST_STATE_NULL );
		music_play_init(0, NULL,1);
			
	
	}
	void mp3_next_song(GtkButton* next_button){

		if(play_song_index+1 < song_index){

			play_song_index=play_song_index+1;
	
		}

		else{
			play_song_index=0;
			
		}

			select_song = ent[play_song_index]->d_name;
			
		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		gst_element_set_state( pipeline, GST_STATE_NULL );
		music_play_init(0, NULL,1);
			

	}

	void mp3_play_button(GtkButton* play_song){

		gst_element_set_state(pipeline, GST_STATE_PLAYING);

	}

	void mp3_pause_button(GtkButton* pause_song){

		gst_element_set_state(pipeline, GST_STATE_PAUSED);

	}

	void mp3_stop_button(GtkButton* stop_song){

		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		gst_element_set_state( pipeline, GST_STATE_NULL );
		music_play_init(0,NULL,0);
		
	
	}

	void mp3_low_volume_button(GtkButton* low_volume){


		
		if(volume>=0){volume=volume-0.1; g_object_set( G_OBJECT(playbin), "volume", volume, NULL );}
	}

	void mp3_high_volume_button(GtkButton* high_volume){

		if(volume<=1.0){volume=volume+0.1; g_object_set( G_OBJECT(playbin), "volume", volume, NULL );}	

	}

	void mp3_return(GtkButton* exit_button){

		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		gst_element_set_state( pipeline, GST_STATE_NULL );

		gtk_widget_show_all(main_window); 
		gtk_widget_hide (mp3_window);
	
	} 





	void mp3_build(){ ///////////////////////////////////NTERFAZ////////////////////////////////*************************************

	GtkWidget* mp3_hbox;
	GtkWidget* mp3_vbox;
	GtkWidget* mp3_hbox_control;

	GtkWidget* back_button;
	GtkWidget* next_button;
	GtkWidget* play_song;
	GtkWidget* pause_song;
	GtkWidget* stop_song;
	GtkWidget* low_volume;
	GtkWidget* high_volume;
	GtkWidget* exit_button;
	
	//GtkWidget* song_label; ///**** INIT
	
	


	mp3=1;
	//WINDOW
	mp3_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(mp3_window), GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(mp3_window, 640, 480);
	gtk_window_set_decorated (GTK_WINDOW(mp3_window),FALSE);
	

	//Init Elements

	back_button = gtk_button_new_with_label("Previous \n Song");
	next_button = gtk_button_new_with_label("Next \n Song");
	play_song = gtk_button_new_with_label("Play");
	pause_song = gtk_button_new_with_label("Pause");
	stop_song = gtk_button_new_with_label("Stop");
	low_volume = gtk_button_new_with_label("Volume Down");
	high_volume = gtk_button_new_with_label("Volume Up");
	exit_button = gtk_button_new_with_label("Return Home");
	song_label= gtk_label_new("");

	//Containers

	mp3_hbox = gtk_hbox_new(FALSE, 0);
	mp3_vbox = gtk_vbox_new(FALSE, 0);
	mp3_hbox_control = gtk_hbox_new(FALSE, 0);

	//VBOX

	gtk_box_pack_start(GTK_BOX(mp3_vbox), exit_button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_vbox), song_label , TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_vbox), mp3_hbox_control, TRUE, TRUE, 0);

	//HBOX_CONTROL

	gtk_box_pack_start(GTK_BOX(mp3_hbox_control), play_song, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_hbox_control), pause_song, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_hbox_control), stop_song, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_hbox_control), low_volume, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_hbox_control), high_volume, TRUE, TRUE, 0);


	//HBOX

	gtk_box_pack_start(GTK_BOX(mp3_hbox), back_button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_hbox), mp3_vbox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mp3_hbox), next_button, TRUE, TRUE, 0);
	

	//add container window

	gtk_container_add(GTK_CONTAINER(mp3_window), mp3_hbox);

	//Connect Signals

	g_signal_connect(back_button, "clicked", G_CALLBACK(mp3_back_song), NULL);
	g_signal_connect(next_button, "clicked", G_CALLBACK(mp3_next_song), NULL);
	g_signal_connect(play_song, "clicked", G_CALLBACK(mp3_play_button), NULL);
	g_signal_connect(pause_song, "clicked", G_CALLBACK(mp3_pause_button), NULL);	
	g_signal_connect(stop_song, "clicked", G_CALLBACK(mp3_stop_button), NULL);	
	g_signal_connect(low_volume, "clicked", G_CALLBACK(mp3_low_volume_button), NULL);
	g_signal_connect(high_volume, "clicked", G_CALLBACK(mp3_high_volume_button), NULL);
	g_signal_connect(exit_button, "clicked", G_CALLBACK(mp3_return), NULL);



	gtk_widget_modify_bg(mp3_window, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(back_button, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(next_button, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(play_song, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(pause_song, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(stop_song, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(low_volume, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(high_volume, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(exit_button, GTK_STATE_NORMAL, &black);


	gtk_widget_modify_bg(mp3_window, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(back_button, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(next_button, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(play_song, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(pause_song, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(stop_song, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(low_volume, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(high_volume, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(exit_button, GTK_STATE_PRELIGHT, &neon_green);

		gtk_label_set_text (GTK_LABEL(song_label), select_song);
	   	gtk_widget_show_all(mp3_window);
		gtk_widget_hide (list_window);
		music_play_init(0,NULL,1);


	}


	

/////////////////////////////////////////MUSICA/////////////////////////////////////////////////////////////////////





static void bus_call(GstBus *bus, GstMessage *msg, GMainLoop *mainloop )
{
    switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_EOS:
        g_print("EOS\n");
        g_main_loop_quit(mainloop);

	gst_element_set_state( pipeline, GST_STATE_NULL );
    	

	if(play_song_index+1 < song_index){

			play_song_index=play_song_index+1;
	
		}

		else{
			play_song_index=0;
			
		}

			select_song = ent[play_song_index]->d_name;
			
		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		gst_element_set_state( pipeline, GST_STATE_NULL );
		music_play_init(0, NULL,1);

	music_play_init(0,NULL,1);

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


///////////////////////////////play init ////////////////////////////////77


void music_play_init( int argc, char *argv[], int state )
{


	char* PATH = function_alpha();

		

    gst_init(&argc, &argv);
    pipeline = gst_pipeline_new( NULL );

    /* Create gstreamer elements */
    playbin = gst_element_factory_make( "playbin2", NULL );
    gst_bin_add( GST_BIN(pipeline), playbin );
    g_object_set( G_OBJECT(playbin), "uri", PATH, NULL );
	g_object_set( G_OBJECT(playbin), "volume", volume, NULL );

	

    /* bus callbacks */
    loop = g_main_loop_new( NULL, FALSE );
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline) );
    gst_bus_add_watch( bus, (GstBusFunc)bus_call, loop );

	if(state==1){
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
	}
		if(state==0){
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
	}

    /* Iterate */
    g_main_loop_run(loop);


    /* Out of the main loop, clean up nicely */
    gst_element_set_state( pipeline, GST_STATE_NULL );
    //gst_object_unref( GST_OBJECT(pipeline) );

	

   
}

char* function_alpha(){


	dir2 = opendir ("/home/nano/Desktop/Empotrados/Interface_proto_1/app/test_music/");

	song_index=0;

   	while ((ent[song_index] = readdir (dir2)) != NULL) {

	if (strcmp(ent[song_index]->d_name, ".") != 0 && strcmp(ent[song_index]->d_name, "..") != 0 ){

   		if(strcmp(select_song, ent[song_index]->d_name)==0) {play_song_index = song_index;}

		song_index = song_index+1;

		if(song_index>99){song_index=99;}


		}

       }

  closedir (dir2);
	
		gtk_label_set_text (GTK_LABEL(song_label), ent[play_song_index]->d_name);
		char* name_with_extension;
		name_with_extension = malloc(strlen(ent[play_song_index]->d_name)+1+strlen(path)); 
		strcpy(name_with_extension, path); /* copy name into the new var */
		strcat(name_with_extension, ent[play_song_index]->d_name); /* add the extension */
		return name_with_extension;
}









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////RADIO//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void array_conv(int station_param){

	station_array[3] = station_param%10; //decimal
	station_param=station_param/10;

	station_array[2] = station_param%10; //unidad
	station_param=station_param/10;

	station_array[1] = station_param%10; //decena
	
 		
	
	if(station_param<10){station_array[0]=0;}

	else{
	station_param=station_param/10;
	station_array[0] = station_param%10; //centena
	}


	set_image();

	

}


void high_volume_button(GtkButton* volume_high){}
void low_volume_button(GtkButton* volume_low){}



	void back_tune_button_clicked(GtkButton* back_tune_button){

		if(station_variable>=810){station_variable=station_variable-1;}

		else{station_variable=1060;}

		array_conv(station_variable);

	}
	void next_tune_button_clicked(GtkButton* next_tune_button){

		if(station_variable<=1060){station_variable=station_variable+1;}

		else{station_variable=810;}

		array_conv(station_variable);

	}

	void change_mode(GtkButton* mode){

		if(aof_text=="AM"){

			aof_text="FM";
			gtk_image_set_from_file(GTK_IMAGE(image_aof),"f.png");

		}

		else{
			aof_text="AM";
			gtk_image_set_from_file(GTK_IMAGE(image_aof),"a.png");

		}
		


		
	}

	void return_button(GtkButton* back){

		gtk_widget_show_all(main_window); 
		gtk_widget_hide (radio_window);

	}

	void fav_button(GtkButton* save_station){

		if(fav_station_save==0){fav_station_1=station_variable;fav_station_save=fav_station_save+1;}
		else{fav_station_2=station_variable;fav_station_save=0;}


	}	

	void fav_button_1_clicked(GtkButton* fav_button_1){

		if(fav_station_1>0){
		station_variable=fav_station_1;

		array_conv(station_variable);
		}

		}

	void fav_button_2_clicked(GtkButton* fav_button_2){

		if(fav_station_2>0){
		station_variable=fav_station_2;
		array_conv(station_variable);
		}

		}
		






void radio_init(){


	GtkWidget* radio_vbox;
	GtkWidget* radio_hbox_top;
	GtkWidget* radio_hbox_images;
	GtkWidget* radio_hbox_tune;
	GtkWidget* radio_hbox_bot;
	
	GtkWidget* volume_high;
	GtkWidget* volume_low;
	GtkWidget* back_tune_button;
	GtkWidget* next_tune_button;
	GtkWidget* mode;
	GtkWidget* back;
	GtkWidget* save_station;
	GtkWidget* fav_button_1;
	GtkWidget* fav_button_2;

	
	

	//WINDOW
	  radio_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	  gtk_window_set_position(GTK_WINDOW(radio_window), GTK_WIN_POS_CENTER);
	  gtk_widget_set_size_request(radio_window, 640, 480);
	  gtk_window_set_decorated (GTK_WINDOW(radio_window),FALSE);


	//Init Elements
	image_decimal = gtk_image_new ();
	image_unidad = gtk_image_new ();
	image_decena = gtk_image_new ();
	image_centena = gtk_image_new ();
	image_aof = gtk_image_new ();
	image_m = gtk_image_new ();
	image_punto = gtk_image_new ();

	volume_high = gtk_button_new_with_label("Volume Up");
	volume_low = gtk_button_new_with_label("Volume Down");
	back_tune_button = gtk_button_new_with_label("Tune Down");
	next_tune_button = gtk_button_new_with_label("Tune Up");
	mode = gtk_button_new_with_label("Change Am / Fm");
	back = gtk_button_new_with_label("Return Home");
	save_station = gtk_button_new_with_label("Favorites");
	fav_button_1 = gtk_button_new_with_label("Fav#1");
	fav_button_2 = gtk_button_new_with_label("Fav#2");

	//Containers

		radio_vbox = gtk_vbox_new(FALSE, 0);
		radio_hbox_top = gtk_hbox_new(FALSE, 0);
		radio_hbox_images = gtk_hbox_new(FALSE, 0);
		radio_hbox_tune = gtk_hbox_new(FALSE, 0);
		radio_hbox_bot = gtk_hbox_new(FALSE, 0);



		//HBOX_TOP

		gtk_box_pack_start(GTK_BOX(radio_hbox_top), back, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_top), mode, TRUE, TRUE, 0);

		//HBOX_IMAGES

		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_centena, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_decena, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_unidad, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_punto, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_decimal, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_aof, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_images), image_m, TRUE, TRUE, 0);

  		//HBOX_TUNE

		gtk_box_pack_start(GTK_BOX(radio_hbox_tune), back_tune_button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_tune), next_tune_button, TRUE, TRUE, 0);

		//HBOX_BOT

		gtk_box_pack_start(GTK_BOX(radio_hbox_bot), fav_button_1, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_bot), fav_button_2, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_bot), save_station, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_bot), volume_high, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_hbox_bot), volume_low, TRUE, TRUE, 0);

		//VBOX 
  		gtk_box_pack_start(GTK_BOX(radio_vbox), radio_hbox_top, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_vbox), radio_hbox_images, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_vbox), radio_hbox_tune, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(radio_vbox), radio_hbox_bot, TRUE, TRUE, 0);


		gtk_container_add(GTK_CONTAINER(radio_window), radio_vbox);

	//Connect Signals

	g_signal_connect(back, "clicked", G_CALLBACK(return_button), NULL);
	g_signal_connect(mode, "clicked", G_CALLBACK(change_mode), NULL);
	g_signal_connect(back_tune_button, "clicked", G_CALLBACK(back_tune_button_clicked), NULL);
	g_signal_connect(next_tune_button, "clicked", G_CALLBACK(next_tune_button_clicked), NULL);
	g_signal_connect(save_station, "clicked", G_CALLBACK(fav_button), NULL);
	g_signal_connect(fav_button_1, "clicked", G_CALLBACK(fav_button_1_clicked), NULL);
	g_signal_connect(fav_button_2, "clicked", G_CALLBACK(fav_button_2_clicked), NULL);
	g_signal_connect(volume_high, "clicked", G_CALLBACK(high_volume_button), NULL);
	g_signal_connect(volume_low, "clicked", G_CALLBACK(low_volume_button), NULL);


	gtk_widget_modify_bg(radio_window, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(back, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(mode, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(back_tune_button, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(next_tune_button, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(save_station, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(fav_button_1, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(fav_button_2, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(volume_high, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(volume_low, GTK_STATE_NORMAL, &black);


	gtk_widget_modify_bg(radio_window, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(back, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(mode, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(back_tune_button, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(next_tune_button, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(save_station, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(fav_button_1, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(fav_button_2, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(volume_high, GTK_STATE_PRELIGHT, &neon_green);
	gtk_widget_modify_bg(volume_low, GTK_STATE_PRELIGHT, &neon_green);

    	gtk_image_set_from_file(GTK_IMAGE(image_aof),"f.png");
	gtk_image_set_from_file(GTK_IMAGE(image_punto),"punto.png");
	gtk_image_set_from_file(GTK_IMAGE(image_m),"m.png");
	array_conv(station_variable);

   
	
	
	

}


	
void set_image(){

	int o=0;

	while (o<4){

		
		switch(station_array[o]){

		case 1: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"1.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "1.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "1.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "1.png"); break;
			}
			break;

		
		case 2: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"2.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "2.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "2.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "2.png"); break;
			}
			break;

		
		case 3: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"3.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "3.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "3.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "3.png"); break;
			}
			break;

		
		case 4: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"4.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "4.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "4.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "4.png"); break;
			}
			break;


		
		case 5: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"5.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "5.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "5.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "5.png"); break;
			}
			break;


		
		case 6: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"6.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "6.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "6.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "6.png"); break;
			}
			break;

		
		case 7: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"7.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "7.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "7.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "7.png"); break;
			}
			break;

		
		case 8: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"8.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "8.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "8.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "8.png"); break;
			}
			break;

		
		case 9: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"9.png");break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "9.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "9.png");break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), "9.png"); break;
			}
			break;

		
		case 0: switch(o){
			case 3: gtk_image_set_from_file(GTK_IMAGE(image_decimal),"0.png"); break;
			case 2: gtk_image_set_from_file(GTK_IMAGE(image_unidad), "0.png"); break;
			case 1: gtk_image_set_from_file(GTK_IMAGE(image_decena), "0.png"); break;
			case 0: gtk_image_set_from_file(GTK_IMAGE(image_centena), NULL);break;
			}
			break; 

			

		}
	
	o=o+1;

	}


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


  mp4_dir = opendir ("/home/nano/Desktop/Empotrados/Interface_proto_1/app/test_mp4/");


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

		char* name =  select_song;
		char* play = "playbin2 uri=file:///home/nano/Desktop/Empotrados/Interface_proto_1/app/test_mp4/";
		char* movie;
		movie = malloc(strlen(name)+1+strlen(play)); 
		strcpy(movie, play); /* copy name into the new var */
		strcat(movie, name); /* add the extension */

		

		 
		gtk_widget_hide (mp4_list_window);
		gtk_widget_show_all(mp4_window);
		init_video(0, NULL, movie);


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




void init_video(int argc, char *argv[], char* path){

  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;
   
  /* Initialize GStreamer */
  gst_init (&argc, &argv);
   
  /* Build the pipeline */
  pipeline = gst_parse_launch (path, NULL);
   
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
