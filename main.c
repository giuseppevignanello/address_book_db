/*
 * address_book_database.c
 * Vestion: 1.0
 *  Author: Peppe
 * Created: 2025-11-17
 * Description: This project is a basic file-based database. It is
 * made for educational purpouses. For the moment it doesn't store
 * any kind of data, but rather a single type of entity that is Contact.
 * So, it is basically a digital address book
 */

#include <stdio.h>
#include <string.h>

typedef struct contact
{
    char name[50];
    char email[50];
} Contact;

/* just create a new contact, For the moment
 * it doesn't get any param, cause thery are hardcoded
 */
int c_contact()
{
    Contact c;

    char n[] = "Peppe";
    strncpy(c.name, n, sizeof(c.name) - 1);

    char em[] = "peppe.vignanello@gmail.com";
    strncpy(c.email, em, sizeof(c.email) - 1);

    // open binary file in append mode
    FILE *fp = fopen("contacts.db", "ab");

    if (!fp)
    {
        perror("Cannot open file");
        return 1;
    }

    // writing just an element to the file
    size_t written = fwrite(&c, sizeof(Contact), 1, fp);

    if (written != 1)
    {
        perror("Error writing contact");
        return 1;
    }

    fclose(fp);

    return 0;
}

/* For the moment this function read all the contacts from the db.
 * Next step is to add one or more params to query the exact contact or contacts that the user wants
 */
int r_contact()
{
    FILE *fp = fopen("contacts.db", "r");

    Contact c;

    while (fread(&c, sizeof(Contact), 1, fp) == 1)
    {
        printf("Name: %s\n Email: %s\n", c.name, c.email);
    }

    fclose(fp);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        perror("You have to pass the operation type");
        return 1;
    }

    if (strcmp(argv[1], "read") == 0)
    {
        // TO DO: pass an hypotetically argv[2] as param
        return r_contact();
    }

    if (strcmp(argv[1], "create") == 0)
    {
        // For the moment the contact is hardcoded
        return c_contact();
    }

    return 0;
}