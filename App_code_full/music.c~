#include <dirent.h>
#include <stdlib.h> 
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>


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


id3tag id3_vector[3];

DIR *dir;
struct dirent *ent;

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
  }

}

int main (int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *list;

  GtkWidget *vbox;
  GtkWidget *label;
  GtkTreeSelection *selection; 

  gtk_init(&argc, &argv);


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 270, 250);
  gtk_window_set_title(GTK_WINDOW(window), "List View");

  list = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  vbox = gtk_vbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

  label = gtk_label_new("");
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(window), vbox);

  init_list(list);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   

   dir = opendir ("/home/nano/Desktop/test_music/");

 	int i=0;

   char* str1="/home/nano/Desktop/test_music/";

   while ((ent = readdir (dir)) != NULL) {

	
   

	

      char* str2=ent->d_name;
      char * str3 = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
      strcpy(str3, str1);
      strcat(str3, str2);
	
	ReadID3(str3, i);
	
	char* n = id3_vector[i].title;
	
   	add_to_list(list, n);

	i=i+1;

	
/*


	string name = strcat("/home/nano/Desktop/test_music/",ent->d_name);

	ReadID3(name, &ID3); 
        printf ("%s\n", ID3.title);

*/

  }

  closedir (dir);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", 
      G_CALLBACK(on_changed), label);

  g_signal_connect(G_OBJECT (window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main ();

  return 0;
}


///////////////////////////////////////////////////////END MAIN////////////////////////////////////////////////////////////////////

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
