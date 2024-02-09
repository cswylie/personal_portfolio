## React Date Picker
Here is a date picker I created using React and JSX in JavaScript.
The picker is composed of two parts, an Entry component, and a Picker component.
### Picker
The Picker allows the user to select a date, which will stay selected even after clicking the next and previous buttons to change the months.
Clicking the display month and year will revert the page back to where the original selected date was.
Clicking a day in a different month within the calendar will switch the display month to be that of the date selected.
### Entry
The Entry component will allow the user to type in a date only in the format of "MM/DD/YYYY." Any attempt to type in another date will not allow the button to be active. 
Selected 'Set' will set the selected date in the Picker to the date inputted by the user. 
