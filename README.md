# Expenses.

## App features
### Users
* ~~Password-protected~~ accounts
* Combine expenses from several accounts (family expenses)
* allows to backup database and keep BU file in a known location. The feature is also useful to transfer 
DB to a different device or to share it with someone.
* using SQLite database

### Structure
* Main page ready to type in next expense. A button from every screen leads to this page
* Available pages: 
  * Settings
  * Statistics
  * Change user
  * history (by default shows this month's expenses sorted by date). Option to load more historical expenses.

### Details
* All settings have default values (except name, password and default currency)
* First time app start 
  * Select language
  * Create a local account (~~pass-protected~~)
  * ~~User may choose to enter pass every time or not~~
  * ~~Enter pass will be required to change user account or change settings~~
* Settings include:
  * Change default currency
  * Add user currency (with exchange rate to the default one)
  * Change user
  * List of expense categories with edit function
    * add new categories 
      * name
      * ~~type (income or expense)~~
      * ~~regular or one-time~~
      * statistics period (weekly, monthly or yearly)
      * limit for the selected period in default currency
    * delete category (only those that have not been used yet)
    * edit category name and type
  * Configure default settings for statistics page:
    * select categories for statistics (Select All option)
    * statistics for the period of time (date from .. to .., week, month, year)
    * statistics in selected currency (add new..)
  * Set total limit for the selected period (day, week, month, year). This will show a warning when exceeded and amount exceeded
* Main page
  * Field ready to accept positive double number
  * Default currency shown with a drop-down list to change currency
  * Drop-down list to select expense category (option to add new)
  * Date of expense (by default set to today)
  * Notes - free text for any notes
  * after expense has been added show average in this category for the configured period (week, month, year)
  * main page will also show current period's total expenses value
* Statistics page
  * change settings on the fly
  * show average expenses for the selected period:
    * by category
    * by regular/non-regular
    * show total expenses, income and delta (+ or -)
    * show average expenses, income and delta (+ or -)
  * switch between overall average and sliding average (configurable time span, default is 3 time periods (weeks, months..)) 
* History page
  * view previous expenses
  * edit each expense (all fields)
  * delete expense
  * combine expenses by category for the selected period of time
### Implementation
* On startup we launch a Startmodule class that checks for existing users and offers to choose user or create new. It then passes selected database file path
and name to DBManager.
If no user exists, then only create new is available. After startup module completes the task it will transfer the selected user's database to main window 
* Using SQlite SQL database. Interface is class *SQL handler class name*. It can add, delete and modify fields in the database
* 
#### Database structure
Expense table:
* Date field (YY-MM-DD). Type:
* Amount field in default currency. Type: double
* Category field. Type: Enum
* Flag income or expense. Type bool. True = expense, False = income
* Flag regular or one-time. Type bool. True = regular, False = one time
Category table:
* Category name
* Statistics period. Type string ("weekly", "monthly", "yearly")
* Limit for the selected period. Type: double
User settings

### Future development
* add support of cloud data storage for shared expenses (family)
* synchronize expenses with cloud DB
* add other users to create family expenses
* each user has his own account and his own expenses, but they can be combined for common statistics. 
Will add additional flag for each expense if it is going to beshared with family or not. 
Expenses that are not share will not be added to statistics.
