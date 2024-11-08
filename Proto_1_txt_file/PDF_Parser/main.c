
/* For PDF parsing we wil be using Poppler library which is a great library when it comes to
parse and extract text from PDF documents */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poppler.h>/* A great library for PDF parsing */

// Function declarations

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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input.pdf>\n", argv[0]);
        return 1;
    }

    /* Get the pdf data */
    char *pdf_data = get_pdf_data(argv[1]);
    if (pdf_data == NULL)
    {
        return 1;
    }
    printf("%s", pdf_data);
    return 0;
}
/* This function will return the absolute path when provided with a filename
we need this as we will use this further to get the URI of the target file
It uses the realpath() function of the C stdlib.
 */
char *get_absolute_path(char *filename)
{
    char *absolute_path = realpath(filename, NULL);
    if (absolute_path == NULL)
    {
        fprintf(stderr, "Error getting absolute path for %s\n", filename);
    }
    /* printf("Absolute path: %s\n", absolute_path); */
    return absolute_path;
}

/* This function returns the URI from the given absolute path using GLIB's g_filename_to_uri(function)
we need it as it is the parameter that is passed to poppler's function
poppler_document_new_from_file().

 */
char *create_uri_from_path(char *absolute_path, GError **error)
{
    char *uri = g_filename_to_uri(absolute_path, NULL, error);
    if (uri == NULL)
    {
        fprintf(stderr, "Error creating URI: %s\n", (*error)->message);
        g_error_free(*error);
    }
    /*     printf("URI: %s\n", uri); */
    return uri;
}

/* This function opens the PDF document and returns the PopplerDocument which is further used to extract the text */
PopplerDocument *open_pdf_document(char *uri, GError **error)
{
    PopplerDocument *document = poppler_document_new_from_file(uri, NULL, error);
    if (document == NULL)
    {
        fprintf(stderr, "Error opening PDF: %s\n", (*error)->message);
        g_error_free(*error);
    }
    return document;
}

/* This function parses the entire document and return the text Content of the PDF */
char *read_pdf(PopplerDocument *document)
{
    int n_pages = poppler_document_get_n_pages(document);
    size_t total_size = 0;

    char *pdf_content = malloc(1); /* to store the text content */
    if (!pdf_content)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    pdf_content[0] = '\0'; /* we initialize with an empty string and then realloc it depending on the content */

    /* Traverse through all the pages and append the content to pdf_content
    during this we realloc the pdf_content to fit the new content
     */
    for (int i = 0; i < n_pages; i++)
    {
        PopplerPage *page = poppler_document_get_page(document, i);
        if (page == NULL)
        {
            fprintf(stderr, "Error getting page %d\n", i);
            continue;
        }

        char *text = poppler_page_get_text(page);
        size_t text_len = strlen(text);

        /* Reallocate the memory to fit the new content */
        pdf_content = realloc(pdf_content, total_size + text_len + 1);
        if (!pdf_content)
        {
            fprintf(stderr, "Memory reallocation failed.\n");
            g_free(text);
            g_object_unref(page);
            return NULL;
        }

        /* Append the text to pdf_content */
        strcat(pdf_content, text);
        total_size += text_len;

        /* Clean up */
        g_free(text);
        g_object_unref(page);
    }

    return pdf_content;
}

/* This function uses all the helper functions above to open pdf and extract the text content and return it */
char *get_pdf_data(char *pdf_filename)
{
    GError *error = NULL;

    /* Get the absolute path of the PDF file */
    char *absolute_path = get_absolute_path(pdf_filename);

    /* Create URI for the PDF file */
    char *uri = create_uri_from_path(absolute_path, &error);

    /* Open the PDF document */
    PopplerDocument *document = open_pdf_document(uri, &error);

    /* Read the content of the PDF */
    char *pdf_content = read_pdf(document);

    /* Clean up */
    g_object_unref(document);
    g_free(uri);
    free(absolute_path);

    return pdf_content; /* return the content */
}

/* This function prints the given PDF content */
void print_pdf_data(char *pdf_content)
{
    printf("PDF Content:\n%s\n", pdf_content);
}