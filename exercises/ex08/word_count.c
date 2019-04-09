
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gmodule.h>


int main(){
  //First we have to read the contents of the file
  gssize num_chars;
  gchar *string_pointer, *filename = "input.txt";
  if (!g_file_get_contents (filename, &string_pointer, &num_chars, NULL)) {
      // Spmething goes wrong
      exit(1);
  }

  //Then we split the file based on spaces. Getting a pointer of string pointers
  gchar** array = g_strsplit(string_pointer," ",-1);
  guint length = g_strv_length(array);
  //Declare our hashtable for easy lookups
  GHashTable * ht = g_hash_table_new (g_str_hash, g_str_equal);
  //Kiio through all the words in the input
  for(int i =0; i < length; i++){
    string_pointer = array[i];//current word
    //Increment value if already in the hashtable or initialize to 1 if not
    if(g_hash_table_contains(ht,string_pointer)){
      //get value pointer
      gpointer val = g_hash_table_lookup(ht, string_pointer);
      //cast and increment
      guint n_val = (((guint)((glong)val)) + 1);
      //recast to pointer and replace
      gpointer n_point = (gpointer) (glong) (n_val);
      g_hash_table_replace(ht, string_pointer, n_point);
    }else{
      //Init value to one and put in hashtable
      guint n_val = 1;
      gpointer n_point = (gpointer) (glong) (n_val);
      g_hash_table_insert(ht, string_pointer, n_point);
    }
  }
  //This loop will go through all the values of the hashtable and print them out
  gpointer* word_set	= g_hash_table_get_keys_as_array (ht,&length);
  for(int i =0; i < length; i++){
      //get word
      string_pointer = (gchar*) word_set[i];
      //get pointer to value
      gpointer val = g_hash_table_lookup(ht, string_pointer);
      //cast and print formatted
      guint n_val = (((guint)((glong)val)));
      g_printf("%s %i\n",string_pointer, n_val);
  }
  //Print number of unique words
  g_printf("%i\n",length);
  return 0;
}
