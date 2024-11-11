#include<poppler.h>
/* This function returns the absolute path of a file */
char *get_absolute_path(char *filename);

/* This function returns URI created from the absolute path */
char *create_uri_from_path(char *absolute_path, GError **error);

/* This function opens a document and returns so that it can be read later*/
PopplerDocument *open_pdf_document(char *uri, GError **error);

/* This function reads the content of the PDF document and returns it*/
char *get_pdf_data(char *pdf_filename);

/* This function prints the PDF content */
void print_pdf_data(char *pdf_content);