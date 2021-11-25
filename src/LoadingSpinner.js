import React, { Component } from 'react';
import './LoadingSpinner.css';

import SpinnerIcon from './images/spinner.svg';

class LoadingSpinner extends Component {
  render() {
    return (
      <div id="spinner">
        <img src={SpinnerIcon} id="spinner-icon" alt="LOADING" />
      </div>
    );
  }
}

export default LoadingSpinner;
