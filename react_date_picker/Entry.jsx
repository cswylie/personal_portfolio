/*
#######################################################################
#
# Copyright (C) 2024 David C. Harrison. All right reserved.
#
# You may not use, distribute, publish, or modify this code without
# the express written permission of the copyright holder.
#
#######################################################################
https://www.regextutorial.org/regex-for-numbers-and-ranges.php
https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_expressions
https://www.geeksforgeeks.org/how-to-disable-a-button-in-reactjs/
*/

import React from 'react';
import PropTypes from 'prop-types';
import './Entry.css';

/**
 * Date entry component.
 */
class Entry extends React.Component {
  /**
   * Constructor
   *
   * this.props.pickerRef.current is a reference to the Picker
   *
   * @param {object} props
   */
  constructor(props) {
    super(props);
    this.state = {
      date: 'MM/DD/YYYY', // Make it an empty default parameter
    };
  }
  /**
   * @param {*} event
   */
  handleInput = (event) => {
    this.setState({
      date: event.target.value,
    });
  };
  setClick = () => {
    this.props.pickerRef.current.setDate(new Date(this.state.date));
  };
  // the reg exp is a little weird for values from 0000->0099 b/c
  // of how the date object works
  /**
   * @return {object}
   */
  render() {
    const re = new RegExp(
        `^(0[1-9]|1[0-2])/` +
        `(0[1-9]|1[0-9]|2[0-9]|3[01])/` +
        `(0[0-9]|1[0-9]|20)\\d{2}$`,
    );
    const test = re.test(this.state.date);
    return (
      <div>
        <input
          id='date'
          data-testid='date'
          type="text"
          value={this.state.date}
          onInput={(event) => this.handleInput(event)}
        />
        <button id='set'
          data-testid='set'
          disabled = {!test}
          onClick={this.setClick}>
          Set
        </button>
      </div>
    );
  }
}

/*
#######################################################################
#######               DO NOT MODIFY BELOW HERE              ###########
#######################################################################
*/

Entry.propTypes = {
  pickerRef: PropTypes.any,
};

export default Entry;
