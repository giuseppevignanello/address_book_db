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
    int id;
    char name[50];
    char email[50];
} Contact;

/* this function just create a new contact, For the moment
 * it doesn't get any param, cause thery are hardcoded
 */
Contact c_contact()
{
    Contact c;
    c.id = 1;

    char n[] = "Peppe";
    strncpy(c.name, n, sizeof(c.name) - 1);

    char em[] = "peppe.vignanello@gmail.com";
    strncpy(c.email, em, sizeof(c.email) - 1);

    return c;
}

int main()
{
    Contact c = c_contact();

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

    return 0;
}