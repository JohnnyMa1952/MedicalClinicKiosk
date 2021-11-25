import React, { Component } from 'react';
import './App.css';

import MedicalIcon from './images/medical-icon.svg';
import Body from './Body.js';

class App extends Component {
  render() {
    return (
      <div className="App">
        <div className="site-header">
          <img src={MedicalIcon} />
          <p>
            Patient Distribution System
          </p>
        </div>
        <div className="body-content">
          <Body />
        </div>
      </div>
    );
  }
}

export default App;
