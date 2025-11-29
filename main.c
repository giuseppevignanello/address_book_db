/*
 * address_book_database.c
 * Vestion: 1.0
 * Author: Peppe
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

/* just create a new contact
 */
int c_contact(char *n, char *em)
{
    Contact c;

    strncpy(c.name, n, sizeof(c.name) - 1);
    c.name[sizeof(c.name) - 1] = '\0';
    strncpy(c.email, em, sizeof(c.email) - 1);
    c.email[sizeof(c.email) - 1] = '\0';

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

/* Reading the email knowing exaclty the name
 */
int r_contact(char *name)
{
    FILE *fp = fopen("contacts.db", "rb");

    Contact c;

    while (fread(&c, sizeof(Contact), 1, fp) == 1)
    {
        if (strcmp(c.name, name) == 0)
        {
            printf("Name: %s\n Email: %s\n", c.name, c.email);
        }
    }

    fclose(fp);

    return 0;
}

int main(int argc, char **argv)
{
    // TODO: add checks for all the values
    if (argc != 2)
    {
        perror("You have to pass the query command");
        return 1;
    }

    char *cmd;
    char *name;
    char *email;

    // getting the query command
    cmd = strtok(argv[1], " ");

    /// strtok maintains an internal static pointer to the next scan position,
    // so passing NULL continues tokenization from where it previously stopped
    name = strtok(NULL, " ");
    email = strtok(NULL, " ");

    if (strcmp(cmd, "read") == 0)
    {
        return r_contact(name);
    }

    if (strcmp(cmd, "create") == 0)
    {
        return c_contact(name, email);
    }

    return 0;
}