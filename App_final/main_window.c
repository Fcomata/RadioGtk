#include <dirent.h>
#include <stdlib.h> 
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

///////////////////////////C.I.////////////////////////////////////

int RW = 0;
itt 3W = 0;
int 4W = 0;
int SW = 0;


////////////////*/////////////MUSICA////////////////////////////


typedef struct _id3tag
{
	char title[30]; 
	char artist[30]; 
	char album[30]; 
	char year[4]; 
	char comment[30];
	unsigned char track; 
	unsigned char genre; 
} id3tag; 


id3tag id3_vector[50];

DIR *dir;
struct dirent *ent;




/////////////////////////MainWindow/////////////////////////////////

GtkBuilder *builder;
GtkWidget  *main_window;
GError     *error = NULL;


////////////////////////////Radio///////////////////////////////////

GtkWidget       *radio_window;

////////////////////////////Mp3///////////////////////////////////


GtkWidget *list_window;
GtkWidget *mp3_window;

////////////////////////////Mp4///////////////////////////////////

GtkWidget *mp4_window;

////////////////////////////Settings///////////////////////////////////

GtkWidget *settings_window;

////////////////////////////HEADER///////////////////////////////////


void list_init();
void radio_init();
void mp3_init();
void mp4_init();
void settings_init();


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
			
			if(3W==0){
				
				list_init();
				3W=1;
			}

			
				gtk_widget_hide (main_window);
				gtk_widget_show_all(list_window);
			
			

		}

void on_mp4_button_window_clicked(GtkButton *mp4_button_window)
{ // HIDE main_window and show mp4_window widget

		
			//if(4W==0){

				//mp4_init();
				//4W=1;

			//}


			//gtk_widget_hide (main_window);
			//gtk_widget_show (mp4_window);

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

   char* str1="/home/nano/Desktop/test_music/";

   while ((ent = readdir (dir)) != NULL) {

 	if(ent->d_name != "." && ent->d_name != ".."  ){
	
   	add_to_list(list, ent->d_name); //cambiar ent->d_name por n para sacar info por id3

	}

       }

  closedir (dir);

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", 
      G_CALLBACK(on_changed), label);

 
}



int ReadID3(const char* Filename, int h)
{
	
	FILE *fp=fopen(Filename,"rb"); 
	char buffer[128]; 
	int x; 

	fseek(fp,-128,SEEK_END); 
	fread(buffer,sizeof(char),sizeof(buffer),fp); 

	if(!(buffer[0]=='T' && buffer[1] == 'A' && buffer[2] == 'G'))
	{
		return 0; 
	}
	
	//Found id3 tag, let's fill out our id3tag struct 
	for(x=0;x<30;x++)
		id3_vector[h].title[x] = buffer[x+3];  //take 3 off cause of TAG 
		id3_vector[h].title[30] = '\0'; 

	for(x=0;x<30;x++)
		id3_vector[h].artist[x] = buffer[x+33]; //33 = TAG + title 
		id3_vector[h].artist[30] = '\0'; 

	for(x=0;x<30;x++)
		id3_vector[h].album[x] = buffer[x+63]; //TAG + title + artist 
		id3_vector[h].album[30] = '\0'; 

	for(x=0;x<4;x++)
		id3_vector[h].year[x] = buffer[x+93]; //TAG + title + artist + album 
		id3_vector[h].year[4] = '\0'; 
		
	for(x=0;x<30;x++)
		id3_vector[h].comment[x] = buffer[x+97]; //TAG + title + artist + album + year 
		id3_vector[h].comment[30] = '\0'; 

	if(buffer[127] > 0 && buffer[127] < 256)
		id3_vector[h].genre = buffer[127]; //If its between 1-255, put it 
	else 
		id3_vector[h].genre = 255; //255 means unused 

	//ID3 1.1 compatibility (Track field) 
	if(id3_vector[h].comment[28] == '\0')
		id3_vector[h].track = id3_vector[h].comment[29]; //If comment ends at 28.. then 29 is the track 
	else
		id3_vector[h].track = 0; //0 mean's unknown track 
	return 1; 
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


	}


	void mp3_return(GtkButton* exit_button){gtk_widget_show_all(main_window); gtk_widget_hide (mp3_window);} ///return de mp3

	void mp3_back_song(GtkButton* back_button){}
	void mp3_next_song(GtkButton* next_button){}

	void mp3_play_button(GtkButton* play_song){}
	void mp3_pause_button(GtkButton* pause_song){}
	void mp3_stop_button(GtkButton* stop_song){}
	void mp3_low_volume_button(GtkButton* low_volume){}
	void mp3_high_volume_button(GtkButton* high_volume){}




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
	void fav_button(GtkButton* save_station){}
	void next_button(GtkButton* forward_station){}
	void back_button(GtkButton* back_station){}
	void move_slider(){}
	void change_mode(GtkButton* mode){}
	void return_button(GtkButton* back){gtk_widget_show_all(main_window); gtk_widget_hide (radio_window);}
		

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////MP4//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

void mp4_list_init(){

 
  GtkWidget *list;
  GtkWidget *vbox;
  GtkWidget *label;
  GtkWidget *button;
  GtkTreeSelection *selection; 

  mp4_list_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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

   dir = opendir ("/home/nano/Desktop/test_mp4/");

   while ((ent = readdir (dir)) != NULL) {

 	if(ent->d_name != "." && ent->d_name != ".."  ){
	
   	add_to_list(list, ent->d_name); //cambiar ent->d_name por n para sacar info por id3

	}

       }

  closedir (dir);

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", 
      G_CALLBACK(on_changed), label);


*/
/////////////////////////////////////////////////Second_ Mp4///////////////////////////////////////////

/*

void mp4_init(){

	GtkBuilder      *builder_mp4;

    builder_mp4 = gtk_builder_new ();
    gtk_builder_add_from_file (builder_mp4, "mp4_window.glade", NULL);
    radio_window = GTK_WIDGET (gtk_builder_get_object (builder_mp4, "mp4_window"));
    gtk_builder_connect_signals (builder_mp4, NULL);
    g_object_unref (G_OBJECT (builder_mp4));


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
////////////////////////////////////////////////////Settings////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

void settings_init(){

    GtkBuilder      *builder_settings;

    builder_settings = gtk_builder_new ();
    gtk_builder_add_from_file (builder_settings, "settings_window.glade", NULL);
    radio_window = GTK_WIDGET (gtk_builder_get_object (builder_settings, "settings_window"));
    gtk_builder_connect_signals (builder_settings, NULL);
    g_object_unref (G_OBJECT (builder_settings));

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
