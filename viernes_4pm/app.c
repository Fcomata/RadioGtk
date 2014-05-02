#include <dirent.h>
#include <stdlib.h> 
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <gst/gst.h>

///////////////////////////////////////////////////////////////

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

////////////////////////////Mp3///////////////////////////////////


GtkWidget *list_window;
GtkWidget *mp3_window;
char* select_song;

char* songs[100];
int song_index=0;
int play_song_index=0;


DIR *mp3_dir;
struct dirent *mp3_ent;

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


		}

void on_settings_button_window_clicked (GtkButton *settings_button_window)
{ // HIDE main_window and show settings_window widget

			 
		}

///////////////////////////////////////////////////main///////////////////////////////////////////////////

int main (int argc, char *argv[])
{


    gtk_init( &argc, &argv );
    builder = gtk_builder_new();
    gtk_builder_add_from_file( builder, "main_window.glade", &error );
    main_window = GTK_WIDGET( gtk_builder_get_object( builder, "main_window" ) );
    gtk_builder_connect_signals( builder, NULL );
    g_object_unref( G_OBJECT( builder ) );
    gtk_widget_show( main_window );
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

	select_song=value;

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

  g_signal_connect(button, "clicked", G_CALLBACK(mp3_init), NULL);

  label = gtk_label_new("");
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_end(GTK_BOX(vbox), label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(list_window), vbox);

  init_list(list);

   mp3_dir = opendir ("/home/nano/Desktop/test_music/");

   while ((mp3_ent = readdir (mp3_dir)) != NULL) {

   		add_to_list(list, mp3_ent->d_name);
		songs[song_index]=mp3_ent->d_name;
		song_index=song_index+1;
		if(song_index>99){song_index=99;}

       }

  closedir (mp3_dir);

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", G_CALLBACK(on_changed), label);

 
}





/////////////////////////////////////Musica_second_window/////////////////////////////////////////////////////////////

	

	void mp3_init(){

		GtkBuilder* mp3_builder;

   	    mp3_builder = gtk_builder_new();
	    gtk_builder_add_from_file( mp3_builder, "mp3_solo.glade", &error );
	    mp3_window = GTK_WIDGET( gtk_builder_get_object( mp3_builder, "mp3_solo" ) );
	    gtk_builder_connect_signals(mp3_builder, NULL );
	    g_object_unref( G_OBJECT( mp3_builder ) );

	   	gtk_widget_show_all(mp3_window);
		gtk_widget_hide (list_window);
		music_play_init(NULL,NULL);


	}


	

	void mp3_back_song(GtkButton* back_button){}
	void mp3_next_song(GtkButton* next_button){}
	void mp3_play_button(GtkButton* play_song){}
	void mp3_pause_button(GtkButton* pause_song){}
	void mp3_stop_button(GtkButton* stop_song){}
	void mp3_low_volume_button(GtkButton* low_volume){}
	void mp3_high_volume_button(GtkButton* high_volume){}

	void mp3_return(GtkButton* exit_button){gtk_widget_show_all(main_window); gtk_widget_hide (mp3_window);} 

	void play(char* song){}
	void pause_song(char* song){}
	void stop(char* song){}
	void set_volume(){}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

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

		char* select_song = "Eternity.mp3";

		char* name =  select_song;
		char* play = "file:///home/nano/Desktop/test_music/";
		char* name_with_extension;
		name_with_extension = malloc(strlen(name)+1+strlen(play)); 
		strcpy(name_with_extension, play); /* copy name into the new var */
		strcat(name_with_extension, name); /* add the extension */

    gst_init(&argc, &argv);
    pipeline = gst_pipeline_new( NULL );

    /* Create gstreamer elements */
    playbin = gst_element_factory_make( "playbin2", NULL );
    gst_bin_add( GST_BIN(pipeline), playbin );
    g_object_set( G_OBJECT(playbin), "uri", "file:///home/nano/Desktop/test_music/Eternity.mp3", NULL );

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
