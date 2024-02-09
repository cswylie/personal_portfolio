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
import {it, expect} from 'vitest';
import {render, screen, fireEvent} from '@testing-library/react';
import App from '../App';
import Picker from '../Picker';

// Just checks for App existence
it('renders', () => {
  render(<App />);
  expect(screen.queryByText('Picker')).not.toBeInTheDocument();
});

// Check that the first of the month is the first of the month
it('renders', async () => {
  render(<Picker />);
  const today = new Date();
  const test = new Date(today.getFullYear(), today.getMonth(), 1);
  const testid = 'd' + test.getDay();
  const firstDay = await screen.findByTestId(testid);
  expect(firstDay.textContent).toEqual('1');
});

// Check today is today
it('renders', async () => {
  render(<Picker />);
  const today = new Date();
  const currDay = await screen.findByTestId('today');
  expect(currDay.textContent).toEqual(`${today.getDate()}`);
});

// Check display is accurate
it('renders', async () => {
  const months = ['January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December'];
  render(<Picker />);
  const today = new Date();
  const displayText = await screen.findByTestId('display');
  expect(displayText.textContent).toEqual(
      `${months[today.getMonth()]} ${today.getFullYear()}`);
});
// Checks for accurate today value
it('renders', async () => {
  render(<Picker />);
  const today = new Date();
  const currDay = await screen.findByTestId('today');
  expect(currDay.textContent).toEqual(`${today.getDate()}`);
});

// Checks if first days are correct
it('renders', async () => {
  render(<Picker />);
  const today = new Date();
  const firstDay = new Date(today.getFullYear(), today.getMonth(), 1);
  const dayBefore = new Date(firstDay-1);
  let d = 0;
  for (let i = dayBefore.getDate()-dayBefore.getDay();
    i <= dayBefore.getDate(); i++) {
    const checkDate = await screen.findByTestId('d'+ d);
    expect(checkDate.textContent).toEqual(`${i}`);
    d++;
  }
});

// Checks if last days are correct
it('renders', async () => {
  render(<Picker />);
  const today = new Date();
  const firstDay = new Date(today.getFullYear(), today.getMonth(), 1);
  const dayBefore = new Date(firstDay-1);
  const lastDay = new Date(today.getFullYear(), today.getMonth()+1, 0);
  let d = 0;
  for (let i = dayBefore.getDate()-dayBefore.getDay();
    i <= dayBefore.getDate(); i++) {
    d++;
  }
  for (let i = 1; i <= lastDay.getDate(); i++) {
    d++;
  }
  for (let i = 1; d < 42; i++) {
    const checkDate = await screen.findByTestId('d'+ d);
    expect(checkDate.textContent).toEqual(`${i}`);
    d++;
  }
});

// today not in next page
it('render', async () => {
  render(<Picker />);
  const next = await screen.findByTestId('next');
  fireEvent.click(next);
  const today = await screen.queryByTestId('today');
  expect(today).not.toBeInTheDocument();
});

// today exists coming back to current page
it('render', async () => {
  render(<Picker />);
  const next = await screen.findByTestId('next');
  fireEvent.click(next);
  const prev = await screen.findByTestId('prev');
  fireEvent.click(prev);
  const today = await screen.queryByTestId('today');
  expect(today).toBeInTheDocument();
});

// today doesn't exist after next prev prev
it('render', async () => {
  render(<Picker />);
  const next = await screen.findByTestId('next');
  fireEvent.click(next);
  for (let i = 0; i < 2; i ++) {
    const prev = await screen.findByTestId('prev');
    fireEvent.click(prev);
  }
  const today = await screen.queryByTestId('today');
  expect(today).not.toBeInTheDocument();
});

// Check that display func works
it('render', async () => {
  const months = ['January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December'];
  const today = new Date();
  render(<Picker />);
  const next = await screen.findByTestId('next');
  fireEvent.click(next);
  const display1 = await screen.findByTestId('display');
  expect(display1.textContent).toEqual(
      `${months[today.getMonth()+1]} ${today.getFullYear()}`);
  const display2 = await screen.findByTestId('display');
  fireEvent.click(display2);
  expect(display2.textContent).toEqual(
      `${months[today.getMonth()]} ${today.getFullYear()}`);
});

// Checks that the clicked date becomes the selected date
it('render', async () => {
  render(<Picker />);
  const selectedDate = await screen.findByTestId('d14');
  fireEvent.click(selectedDate);
  const today = await screen.findByTestId('today');
  expect(selectedDate.textContent).toEqual(today.textContent);
});
