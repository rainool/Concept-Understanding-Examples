#include "splashkit.h"
#include "utilities.h"

using std::to_string;

//role levels (access levels)
enum role_level
{
    NO_ACCESS,
    USER,
    ADMIN,
    SUPER_USER
};

//user data storage
struct user_data
{
    string username;
    role_level role;
};

//role reading from user
role_level read_role()
{
    int role_input = read_integer("Enter your role level (0 = No Access, 1 = User, 2 = Admin, 3 = Super User)");
   
    switch (role_input)
    {
        case 0:
            return NO_ACCESS;
        case 1:
            return USER;
        case 2:
            return ADMIN;
        case 3: 
            return SUPER_USER;
        default:
            write_line("Invalid role. Setting role level to none (0)");
            return NO_ACCESS;
    }
}

string to_string(role_level role)
{
    switch(role)
    {
        case NO_ACCESS:
            return "None";
        case USER:
            return "User";
        case ADMIN:
            return "Admin";
        case SUPER_USER:
            return "Super User";
        default:
            return "Unknown Role Level";
    }
}

void print_user(const user_data& user)
{
    write_line("User Details: ");
    write_line("Username: " + user.username);
    write_line("Role Level: " + to_string(user.role));
}

void update_user(user_data &user)
{
    bool updating = true;
    while (updating)
    {
        write_line("0 - Update Username");
        write_line("1 - Update Role");
        write_line("2 - Update Exit");

        int choice = read_integer("Enter your choice (0-2): ");

        switch(choice)
        {
            case 0:
                user.username = read_string("Enter new username: ");
                break;
            case 1:
                user.role = read_role();
                break;
            case 2:
                updating = false;
                break;
            default:
                write_line("Invalid");
                break;
        }
    }
}

int main()
{
    user_data user ={
        "my_admin",
        ADMIN
    };

    update_user(user);
    print_user(user);

    return 0;
}
