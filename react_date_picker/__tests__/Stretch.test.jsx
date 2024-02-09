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
import Entry from '../Entry';

it('renders', () => {
  render(<App />);
  expect(screen.queryByText('Hello')).not.toBeInTheDocument();
});

// Check for date existence
it('renders', async () => {
  render(<Entry />);
  const date = await screen.findByTestId('date');
  expect(date).toBeInTheDocument();
});

// Check for set button existence
it('renders', async () => {
  render(<Entry />);
  const set = await screen.findByTestId('set');
  expect(set).toBeInTheDocument();
});

// Checks if the date input actually takes input
it('renders', async () => {
  render(<App />);
  const date = await screen.findByTestId('date');
  fireEvent.input(date, {target: {value: '10/28/2003'}});
  expect(date.getAttribute('value')).toEqual('10/28/2003');
});

// Checks that the button is disabled on wrong input
it('renders', async () => {
  render(<App />);
  const date = await screen.findByTestId('date');
  fireEvent.input(date, {target: {value: '23/45/1995'}});
  const set = await screen.findByTestId('set');
  expect(set.getAttribute('disabled')).toBeFalsy();
});

// Checks that the date set button works
it('renders', async () => {
  render(<App />);
  const date = await screen.findByTestId('date');
  fireEvent.input(date, {target: {value: '10/28/2003'}});
  const set = await screen.findByTestId('set');
  fireEvent.click(set);
  const today = await screen.findByTestId('today');
  expect(today.textContent).toEqual('28');
});
