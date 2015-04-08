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
  $groups = array('Additional_Data');
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