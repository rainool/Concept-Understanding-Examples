#include "splashkit.h"
#include "utilities.h"


using std::to_string;

const int SIZE = 100;

struct product_info
{
    string name;
    double cost;
    double sale_price;
    int product_qty;
};

struct shop
{
    product_info products[SIZE];
    int product_count = 0;
    double total_sales = 0;
    double total_profit = 0;
};

//function to create new shop
shop create_shop()
{
    shop new_shop;
    new_shop.product_count = 0;
    new_shop.total_sales = 0;
    new_shop.total_profit = 0;
    return new_shop;
}

void add_product(shop& store)
{
    if(store.product_count >= SIZE)
    {
        write_line("The store management system has reached it's maximum product capacity.");
        return;
    }

    product_info &new_product = store.products[store.product_count];
    new_product.name = read_string("Enter product name: ");
    new_product.cost = read_double("Enter product cost: $");
    new_product.sale_price = read_double("Enter product sale price: $");
    new_product.product_qty = read_integer("Enter product stock quantity: ");

    store.product_count++;
    write_line("Product has been added successfully.");
}

int find_product(const shop& store, const string &search_name)
{
    for (int i = 0; i < store.product_count; i++)
    {
        if(store.products[i].name == search_name)
        {
            return i;
        }
    }

    return 101;
}

void remove_product(shop& store)
{
    string search_name = read_string("Enter a product name to remove: ");
    int index = find_product(store, search_name);

    if(index == 101)
    {
        write_line("This product does not exist.");
        return;
    }

    for(int i = index; i < store.product_count - 1; i++)
    {
        store.products[i] = store.products[i + 1];
    }
    store.product_count--;
    write_line("Product has been deleted.");
}

void update_product(shop& store)
{
    string search_name = read_string("Enter a product name to update: ");
    int index = find_product(store, search_name);

    if(index == 101)
    {
        write_line("This product does not exist.");
        return;
    }

    product_info& product = store.products[index];
    bool updating = true;

    while(updating)
    {
        write_line("Product Details:");
        write_line("Product Name: " + product.name);
        write_line("Cost Price: " + to_string(product.cost));
        write_line("Sale Price: " + to_string(product.sale_price));
        write_line("Quantity on hand: " + to_string(product.product_qty));

        write_line("1 - Update Name");
        write_line("2 - Update Cost Price");
        write_line("3 - Update Sale Price");
        write_line("4 - Update Quantity on hand");
        write_line("5 - Quit Update");

        int option = read_integer("Enter your choice: ");

        switch(option)
        {
            case 1:
                product.name = read_string("Enter new name:");
                break;
            case 2:
                product.cost = read_double("Enter new cost price: $");
                break;
            case 3:
                product.sale_price = read_double("Enter new sale price: $");
                break;
            case 4:
                product.product_qty = read_integer("Enter new quantity on hand: ");
                break;
            case 5:
                updating = false;
                break;
            default:
                write_line("Invalid option");
        }
    }
}

void sell_product(shop& store)
{
    string search_name = read_string("Enter the product name to sell: ");
    int index = find_product(store, search_name);

    if (index == 101)
    {
        write_line("This product does not exist");
    }

    product_info &product = store.products[index];
    int quantity = read_integer("Enter quantity to sell: ");

    if(quantity > product.product_qty)
    {
        write_line("Not enough stock available.");
    }
    else
    {
        double sale_value = quantity * product.sale_price;
        double profit = sale_value - (quantity * product.cost);

        store.total_sales += sale_value;
        store.total_profit += profit;
        product.product_qty -= quantity;

        write_line("Sale completed.");
    }

}

void print_status(const shop& store)
{
    write_line("Shop Status:");
    write_line("Total Sales: " + to_string(store.total_sales));
    write_line("Total Profit: " + to_string(store.total_profit));
    write_line("Number of Products: " + to_string(store.product_count));

    double stock_value = 0;
    int low_stock_count = 0;

    for( int i = 0; i < store.product_count; i++)
    {
        const product_info &product = store.products[i];
        stock_value += product.cost * product.product_qty;

        if(product.product_qty < 10)
        {
            low_stock_count++;
        }
    }

    write_line("Current stock value: $" + to_string(stock_value));
    write_line("Number of products with low stock: " + to_string(low_stock_count));
}


int main()
{
    shop my_shop = create_shop(); 
    bool quit = false;

    while(!quit)
    {
        write_line("Welcome to the store management system.");
        write_line("This is a program written by Ryan Liu s224476007");
        write_line("================================================");
        write_line("1 - Add Product");
        write_line("2 - Remove Product");
        write_line("3 - Update Product");
        write_line("4 - Sell Product");
        write_line("5 - Print Status");
        write_line("6 - Quit");
        
        int choice = read_integer("Enter your choice (1-6): ");
        switch (choice)
        {
            case 1:
                add_product(my_shop);
                break;
            case 2:
                remove_product(my_shop);
                break;
            case 3:
                update_product(my_shop);
                break;
            case 4:
                sell_product(my_shop);
                break;
            case 5:
                print_status(my_shop);
                break;
            case 6:
                quit = true;
                break;
        }
    }
    write_line("Thank you for using the shop management system! ");
    return 0;
}