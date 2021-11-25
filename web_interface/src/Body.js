import React, { Component } from 'react';
import './Body.css';

import ClinicItem from './ClinicItem.js';
import LoadingSpinner from './LoadingSpinner.js';

class Body extends Component {
  constructor(props) {
    super(props);
    this.state = {
      clinicList: [],
      isLoading: false,
    };
    this._refreshPage = this._refreshPage.bind(this);
  }

  _refreshPage() {
    this._retrieveClinicData();
  }

  _retrieveClinicData() {
    this.setState({isLoading: true});
    fetch('http://kevinpi.ddns.net/clinics', {
      method: 'GET',
    }).then((res) => res.json())
    .then((response) => {
      if (response.error) {
        console.warn('Error!', response.error);
      } else {
        this.setState({clinicList: response, isLoading: false});
      }
      // Gonna wanna set isLoading false HERE instead, with error message if needed
    })
    .catch((error) => {
      console.warn('Error: ', error);
    });
  }

  componentWillMount() {
    document.addEventListener("keydown", this._handleEsc, false);
    this._retrieveClinicData();
  }
  
  _renderClinics() {
    return this.state.isLoading ?
    (
    <div className="spinner-wrapper">
      <LoadingSpinner />
    </div>
    )
    :
    this.state.clinicList.map((item, index) => {
      return (
        <ClinicItem key={index} {...item} onRefresh={this._refreshPage} />
      )
    });
  }

  render() {
    return (
      <div className="body">
        {this._renderClinics()}
      </div>
    );
  }
}

export default Body;
