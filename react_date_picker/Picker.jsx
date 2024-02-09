/*
#######################################################################
#
# Copyright (C) 2020-2024 David C. Harrison. All right reserved.
#
# You may not use, distribute, publish, or modify this code without
# the express written permission of the copyright holder.
#
#######################################################################
*/
import React from 'react';
import './Picker.css';

/**
 * Picker component.
 */
class Picker extends React.Component {
  /**
   * Constructor
   * @param {object} props
   */
  constructor(props) {
    super(props);
    this.state = {
      displayDate: new Date(),
      selectedDate: new Date(), // current seleted date
    };
  }
  // Don't Forget to Alter Linter Before Submit
  // Functions-------------------------------
  handleClickPrev = () => {
    this.setState({
      displayDate: new Date(this.state.displayDate.getFullYear(),
          this.state.displayDate.getMonth()-1, 1),
    });
  };
  handleClickNext = () => {
    this.setState({
      displayDate: new Date(this.state.displayDate.getFullYear(),
          this.state.displayDate.getMonth()+1, 1),
    });
  };
  handleClickDisplay = () => {
    this.setState({
      displayDate: this.state.selectedDate,
    });
  };
  /*
    This used to be called a different name function, and setDate was a
    different function, but they both did the same thing, so I simply
    changed the name to setDate as was required.
   */
  setDate = (date) => {
    this.setState({
      displayDate: new Date(date.getFullYear(), date.getMonth(), 1),
      selectedDate: date,
    });
  };
  // Function that is used specifically for checking if two dates are
  // the same. Used below to highlight the selectedDate, checking if
  // the div date matches the selected date, and it is used to assign
  // the 'today' id to a specific div as well
  checkDateEquivalence = (date1, date2) => {
    return ((date1.getFullYear() === date2.getFullYear()) &&
        (date1.getMonth() === date2.getMonth()) &&
        (date1.getDate() === date2.getDate()) &&
        date2.getMonth() === this.state.displayDate.getMonth());
  };
  // ----------------------------------------
  /**
   * @return {object} a <div> containing the picker
   */
  render() {
    const months = ['January', 'February', 'March', 'April', 'May', 'June',
      'July', 'August', 'September', 'October', 'November', 'December'];
    const pickerDays = getAllDays(this.state.displayDate.getFullYear(),
        this.state.displayDate.getMonth());

    return (
      <div>
        <div className='displayDate'>
          <div id='prev'
            data-testid ='prev'
            onClick= {this.handleClickPrev}>
            {'<'}
          </div>
          <div id='display'
            data-testid ='display'
            onClick={this.handleClickDisplay}>
            {months[this.state.displayDate.getMonth()] + ' ' +
              this.state.displayDate.getFullYear()}
          </div>
          <div id='next'
            data-testid ='next'
            onClick={this.handleClickNext}>
            {'>'}
          </div>
        </div>
        <div className='weekdays'>
          <div>S</div>
          <div>M</div>
          <div>T</div>
          <div>W</div>
          <div>T</div>
          <div>F</div>
          <div>S</div>
        </div>
        <div className='calendar'>
          {pickerDays.map((d, i)=>(
            <div onClick={() => this.setDate(d)}
              key={i}
              data-testid={`${(this.checkDateEquivalence(d,
                  this.state.selectedDate)) ? 'today' : ('d' + i)}`}
              id={`${(this.checkDateEquivalence(d,
                  this.state.selectedDate)) ? 'today' : ('d' + i)}`}
              className='day'>
              {d.getDate()}
            </div>
          ))}
        </div>
      </div>
    );
  }
}

/**
 * Returns array of Date Objects that fill Table
 * @param {object} year
 * @param {object} month
 * @return {object}
*/
function getAllDays(year, month) {
  const firstDay = new Date(year, month, 1);
  const lastDay = new Date(year, month+1, 0);
  const start = new Date(firstDay-1);// Subtract firstDay Days for start
  const end = new Date(lastDay.getFullYear(), lastDay.getMonth()+1, 1);
  let count = 0;
  const days = [];
  if (firstDay.getDay() != 0) { // makes it so that it will actually start on S
    for (let i = start.getDate() - start.getDay(); i <= start.getDate(); i++) {
      days.push(new Date(start.getFullYear(), start.getMonth(), i));
      count ++;
    }
  } for (let i = 1; i <= lastDay.getDate(); i++) {
    days.push(new Date(firstDay.getFullYear(), firstDay.getMonth(), i));
    count ++;
  } for (let i = 1; count < 42; i++) { // 42 for 42 different cells
    days.push(new Date(end.getFullYear(), end.getMonth(), i));
    count ++;
  }
  return days;
}

export default Picker;
