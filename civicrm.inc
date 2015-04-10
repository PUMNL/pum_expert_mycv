<?php

function pum_expert_mycv_civi_save_education($contact_id, $data, $num_educations) {
  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
  $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
  foreach($custom_fields['values'] as $field) {
    $fields[$field['name']] = 'custom_'.$field['id'];
  }

  $educations = pum_expert_mycv_get_civi_education($contact_id);
  $education_params = array();
  $educations_to_remove = array();
  if ($num_educations < count($educations)) {
    for($i=count($educations); $i > $num_educations; $i--) {
      $educations_to_remove[] = $educations[$i-1]['id'];
    }
  }

  $newId = -1;
  for($i=0; $i < $num_educations; $i++) {
    if (isset($educations[$i])) {
      $key = $educations[$i]['id'];
    } else {
      $key = $newId;
      $newId --;
    }

    $education_params[$fields['Name_of_Institution'].':'.$key] = $data['education_institution_name_'.$i];
    $education_params[$fields['Field_of_study_major'].':'.$key] = $data['education_field_of_study_'.$i];
    $education_params[$fields['City'].':'.$key] = $data['education_city_'.$i];
    $education_params[$fields['Country'].':'.$key] = $data['education_country_'.$i];
    $education_params[$fields['Education_level'].':'.$key] = $data['education_education_level_'.$i];
    $education_params[$fields['Years_From'].':'.$key] = $data['education_years_from_'.$i];
    $education_params[$fields['To'].':'.$key] = $data['education_to_'.$i];
    $education_params[$fields['Diploma_Degree'].':'.$key] = $data['education_diploma_degree_'.$i];
  }

  if (count($education_params)) {
    $education_params['entity_id'] = $contact_id;
    civicrm_api3('CustomValue', 'create', $education_params);
  }

  if (count($educations_to_remove) > 0) {
    CRM_Core_DAO::executeQuery("DELETE FROM `".$group_info['table_name']."` WHERE `id` IN (".implode(",", $educations_to_remove).")");
  }
}

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
  $home_loc = civicrm_api3('LocationType', 'getvalue', array('return' => 'id', 'name' => 'Home'));
  try {
    $home_address = civicrm_api3('Address', 'getsingle', array(
      'contact_id' => $contact['id'],
      'location_type_id' => $home_loc
    ));
  } catch (Exception $e) {
    $home_address['id'] = false;
    $home_address['street_address'] = '';
    $home_address['postal_code'] = '';
    $home_address['city'] = '';
    $home_address['country_id'] = 1152; //netherlands by default
  }
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