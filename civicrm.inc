<?php

function pum_expert_mycv_get_civi_contact() {
  static $contact = false;
  if (!empty($contact)) {
    return $contact;
  }

  civicrm_initialize();
  $session = CRM_Core_Session::singleton();

  $contact = civicrm_api3('Contact', 'getsingle', array('id' => $session->get('userID')));
  $custom_fields = _pum_expert_mycv_get_custom_fields();
  $params = array();
  $params['id'] = $session->get('userID');
  foreach($custom_fields as $field) {
    $params['return.custom_'.$field['id']] = 1;
  }
  $custom_data = civicrm_api3('Contact', 'getsingle', $params);
  foreach($custom_data as $key => $val) {
    $contact[$key] = $val;
    if (isset($custom_fields[$key])) {
      $field = $custom_fields[$key];
      $contact[$field['custom_group_name'].'::'.$field['name']] = $val;
    }
  }

  //get address info
  $home_address = array();
  $home_loc = civicrm_api3('LocationType', 'getvalue', array('return' => 'id', 'name' => 'Home'));
  try {
    $home_address = civicrm_api3('Address', 'getsingle', array(
      'contact_id' => $contact['id'],
      'location_type_id' => $home_loc
    ));
  } catch (Exception $e) {
    //do nothing
  }

  $home_address['id'] = isset($home_address['id']) ? $home_address['id'] : false;
  $home_address['street_address'] = isset($home_address['street_address']) ? $home_address['street_address'] : '';
  $home_address['postal_code'] = isset($home_address['postal_code']) ? $home_address['postal_code'] : '';
  $home_address['city'] = isset($home_address['city']) ? $home_address['city'] : '';
  $home_address['country_id'] = isset($home_address['country_id']) && !empty($home_address['country_id']) ? $home_address['country_id'] : 1152; //netherlands by default
  $contact['home_address'] = $home_address;

  //get phone info
  $phone_type = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'phone_type'));
  $home_phone_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Phone', 'option_group_id' => $phone_type));
  $fax_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Fax', 'option_group_id' => $phone_type));
  $mobile_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Mobile', 'option_group_id' => $phone_type));

  try {
    $home_phone = civicrm_api3('Phone', 'getsingle', array('contact_id' => $contact['id'], 'phone_type_id' => $home_phone_type));
  } catch (Exception $e) {
    $home_phone['id'] = false;
    $home_phone['phone_type_id'] = $home_phone_type;
    $home_phone['phone'] = '';
  }
  $contact['home_phone'] = $home_phone;

  try {
    $mobile_phone = civicrm_api3('Phone', 'getsingle', array('contact_id' => $contact['id'], 'phone_type_id' => $mobile_type));
  } catch (Exception $e) {
    $mobile_phone['id'] = false;
    $mobile_phone['phone_type_id'] = $mobile_type;
    $mobile_phone['phone'] = '';
  }
  $contact['mobile'] = $mobile_phone;

  try {
    $fax = civicrm_api3('Phone', 'getsingle', array('contact_id' => $contact['id'], 'phone_type_id' => $fax_type));
  } catch (Exception $e) {
    $fax['id'] = false;
    $fax['phone_type_id'] = $fax_type;
    $fax['phone'] = '';
  }
  $contact['fax'] = $fax;

  try {
    $email = civicrm_api3('Email', 'getsingle', array('contact_id' => $contact['id'], 'is_primary' => 1));
  } catch (Exception $e) {
    $email['id'] = false;
    $email['email'] = '';
  }
  $contact['email'] = $email;


  return $contact;
}

function _pum_expert_mycv_get_custom_field_id_by_name($name) {
  foreach(_pum_expert_mycv_get_custom_fields() as $field) {
    $key = $field['custom_group_name'].'::'.$field['name'];
    if ($key == $name) {
      return $field['id'];
    }
  }
}

function _pum_expert_mycv_get_custom_fields() {
  $groups = array('Additional_Data', 'Passport_Information', 'Nationality', 'In_Case_of_Emergency_Contact', 'Medical_Information', 'Bank_Information', 'expert_data');
  $fields = array();
  foreach($groups as $group) {
    $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => $group));
    $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
    foreach($custom_fields['values'] as $field) {
      $fields['custom_'.$field['id']] = array(
        'name' => $field['name'],
        'id' => $field['id'],
        'custom_group_id' => $field['custom_group_id'],
        'custom_group_name' => $group_info['name'],
      );
    }
  }
  return $fields;
}