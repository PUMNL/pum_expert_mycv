<?php

require_once('civicrm.inc');
require_once('education.inc');
require_once('workhistory.inc');

function candidate_expert_cv($form, &$form_state) {

  if(isset($form_state['values'])) {
    $currstep = $form_state['step'] + 1;
  }else {
    $currstep = 0;
  }
  $form_state['step'] = $currstep;

  $allsteps = candidate_expert_cv_get_forms($form_state, $currstep);
  $currform['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>'.$allsteps[$currstep]['title'].' ('.($currstep+1).'/'.count($allsteps).')</h2>',
  );
  $currform['form'] =  $allsteps[$currstep]['form'];

  if (($currstep+1) > 1) {
    $currform['previous']['#type'] = 'submit';
    $currform['previous']['#value'] = t('Previous');
    $currform['previous']['#submit'] = array('candidate_expert_cv_previous');
    $currForm['previous']['#limit_validation_errors'] = array();
  }

  if (($currstep+1) == count($allsteps)) {
    $currform['next']['#type'] = 'submit';
    $currform['next']['#value'] = t('Submit');
  } else {
    $currform['next']['#type'] = 'submit';
    $currform['next']['#value'] = t('Next');
  }

  $form_state['next'] = false;

  $currform['#validate'] = array('candidate_expert_cv_validate_code_of_conduct');

  return $currform;
}

function candidate_expert_cv_validate_code_of_conduct($form, &$form_state) {
  $allsteps = candidate_expert_cv_get_forms($form_state, $form_state['step']);
  if (($form_state['step']+1) == count($allsteps) && $form_state['values']['op'] == t('Submit') && empty($form_state['values']['code_of_conduct'])) {
    form_set_error('code_of_conduct', t('You didn\'t agree to the Code of Conduct'));
  }
}

function candidate_expert_cv_previous($form, &$form_state) {
  $form_state['step'] = $form_state['step'] - 2;
  $form_state['rebuild'] = TRUE;
}

function candidate_expert_cv_submit($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  if($form_state['step'] + 1 != count(candidate_expert_cv_get_forms($form_state, $form_state['step']))) {
    $form_state['next'] = true;
    $form_state['rebuild'] = TRUE;
  }else {
    //store the form
    $session = CRM_Core_Session::singleton();
    $original_contact = pum_expert_mycv_get_civi_contact();
    $contact['id'] = $session->get('userID');
    $contact['prefix_id'] = $form_state['storedvalues'][0]['prefix'];
    $contact['first_name'] = $form_state['storedvalues'][0]['first_name'];
    $contact['middle_name'] = $form_state['storedvalues'][0]['middle_name'];
    $contact['last_name'] = $form_state['storedvalues'][0]['last_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Additional_Data::Initials')] = $form_state['storedvalues'][0]['initials'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Additional_Data::City_of_Birth')] = $form_state['storedvalues'][0]['city_of_birth'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Additional_Data::Country_of_Birth')] = $form_state['storedvalues'][0]['country_of_birth'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Nationality::Nationality')] = $form_state['storedvalues'][0]['nationality'];

    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Name')] = $form_state['storedvalues'][0]['passport_first_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Name_Last_Name')] = $form_state['storedvalues'][0]['passport_last_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Name_Partner_Last_Name')] = $form_state['storedvalues'][0]['passport_partner_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Number')] = $form_state['storedvalues'][0]['passport_number'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Valid_until')] = _pum_expert_cv_form_date_submitted_string_value($form_state['storedvalues'][0]['passport_valid_until']);

    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::Relationship_with_contact')] = $form_state['storedvalues'][0]['ice_relationship'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::Other_relationship')] = $form_state['storedvalues'][0]['ice_other'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::First_name_contact')] = $form_state['storedvalues'][0]['ice_first_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::Last_name_contact')] = $form_state['storedvalues'][0]['ice_last_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::Phone_number_1')] = $form_state['storedvalues'][0]['ice_phone_1'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::Phone_number_2')] = $form_state['storedvalues'][0]['ice_phone_2'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('In_Case_of_Emergency_Contact::Email_Address')] = $form_state['storedvalues'][0]['ice_email'];

    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Medical_Information::Health_Insurance_Company')] = $form_state['storedvalues'][1]['health_insurance_company'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Medical_Information::Health_Insurance_Number')] = $form_state['storedvalues'][1]['health_insurance_number'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Medical_Information::Health_Insurance_Country')] = $form_state['storedvalues'][1]['health_insurance_country'];

    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Bank_Account_Number')] = $form_state['storedvalues'][1]['bank_account_number'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::IBAN_nummer')] = $form_state['storedvalues'][1]['iban_number'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::BIC_Swiftcode')] = $form_state['storedvalues'][1]['bic'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Accountholder_name')] = $form_state['storedvalues'][1]['accountholder_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Bank_Name')] = $form_state['storedvalues'][1]['bank_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Bank_City')] = $form_state['storedvalues'][1]['bank_city'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Bank_Country_ISO_Code')] = $form_state['storedvalues'][1]['bank_country'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Accountholder_address')] = $form_state['storedvalues'][1]['accountholder_address'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Accountholder_postal_code')] = $form_state['storedvalues'][1]['accountholder_postal_code'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Accountholder_city')] = $form_state['storedvalues'][1]['accountholder_city'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Accountholder_country')] = $form_state['storedvalues'][1]['accountholder_country'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Bank_Information::Other_Bank_Information_Comments')] = $form_state['storedvalues'][1]['other_bank_information'];

    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('expert_data::code_conduct')] = $form_state['storedvalues'][4]['code_of_conduct'] ? 'Yes' : '';

    civicrm_api3('Contact', 'create', $contact);

    $address['contact_id'] = $contact['id'];
    if ($original_contact['home_address']['id']) {
      $address['id'] = $original_contact['home_address']['id'];
    }
    $address['street_address'] = $form_state['storedvalues'][0]['street_address'];
    $address['postal_code'] = $form_state['storedvalues'][0]['postal_code'];
    $address['city'] = $form_state['storedvalues'][0]['city'];
    $address['country_id'] = $form_state['storedvalues'][0]['country_id'];
    $address['location_type_id'] = $original_contact['home_address']['location_type_id'];
    civicrm_api3('Address', 'create', $address);

    if (!empty($form_state['storedvalues'][0]['phone'])) {
      $phone['phone'] = $form_state['storedvalues'][0]['phone'];
      $phone['is_primary'] = 1;
      $phone['contact_id'] = $contact['id'];
      $phone['phone_type_id'] = $original_contact['home_phone']['phone_type_id'];
      if ($original_contact['home_phone']['id']) {
        $phone['id'] = $original_contact['home_phone']['id'];
      }
      civicrm_api3('Phone', 'create', $phone);
    } elseif ($original_contact['home_phone']['id']) {
      civicrm_api3('Phone', 'delete', array('id' => $original_contact['home_phone']['id']));
    }

    if (!empty($form_state['storedvalues'][0]['mobile'])) {
      $mobile['phone'] = $form_state['storedvalues'][0]['mobile'];
      $mobile['contact_id'] = $contact['id'];
      $mobile['phone_type_id'] = $original_contact['mobile']['phone_type_id'];
      if ($original_contact['mobile']['id']) {
        $mobile['id'] = $original_contact['mobile']['id'];
      }
      civicrm_api3('Phone', 'create', $mobile);
    } elseif ($original_contact['mobile']['id']) {
      civicrm_api3('Phone', 'delete', array('id' => $original_contact['mobile']['id']));
    }

    if (!empty($form_state['storedvalues'][0]['fax'])) {
      $fax['phone'] = $form_state['storedvalues'][0]['fax'];
      $fax['contact_id'] = $contact['id'];
      $fax['phone_type_id'] = $original_contact['fax']['phone_type_id'];
      if ($original_contact['fax']['id']) {
        $fax['id'] = $original_contact['fax']['id'];
      }
      civicrm_api3('Phone', 'create', $fax);
    } elseif ($original_contact['fax']['id']) {
      civicrm_api3('Phone', 'delete', array('id' => $original_contact['fax']['id']));
    }

    if (!empty($form_state['storedvalues'][0]['email'])) {
      $email['email'] = $form_state['storedvalues'][0]['email'];
      $email['contact_id'] = $contact['id'];
      $email['is_primary'] = 1;
      if ($original_contact['email']['id']) {
        $email['id'] = $original_contact['email']['id'];
      }
      civicrm_api3('Email', 'create', $email);
    } elseif ($original_contact['email']['id']) {
      civicrm_api3('Email', 'delete', array('id' => $original_contact['email']['id']));
    }

    //update education
    pum_expert_mycv_civi_save_education($contact['id'], $form_state['storedvalues'][2], $form_state['num_educations']);

    //update work history
    pum_expert_mycv_civi_save_workhistory($contact['id'], $form_state['storedvalues'][3], $form_state['num_workhistory']);

    //create activity in case and update case
    $case_status_id = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_status'));
    $current_status[] = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Assess CV', 'option_group_id' => $case_status_id));
    $current_status[] = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Accepted', 'option_group_id' => $case_status_id));
    $current_status[] = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Fill Out PUM CV', 'option_group_id' => $case_status_id));
    $current_status[] = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Final Check Application', 'option_group_id' => $case_status_id));
    $current_status[] = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Interview', 'option_group_id' => $case_status_id));

    $case_id = CRM_Core_DAO::singleValueQuery("SELECT civicrm_case.id from civicrm_case inner join civicrm_case_contact on civicrm_case.id = civicrm_case_contact.case_id where civicrm_case.status_id IN (".implode(", ", $current_status).") AND civicrm_case_contact.contact_id = %1", array(1 => array($contact['id'], 'Integer')));
    if ($case_id) {
      $new_status_id = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Fill Out PUM CV', 'option_group_id' => $case_status_id));
      $activity_type_id = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Fill Out PUM CV', 'option_group_id' => 2));
      $activity_params['case_id'] = $case_id;
      $activity_params['subject'] = 'Expert PUM CV filled out';
      $activity_params['status_id'] = 2; //completed
      $activity_params['activity_type_id'] = $activity_type_id;
      civicrm_api3('Activity', 'create', $activity_params);
      $case_params['id'] = $case_id;
      $case_params['status_id'] = $new_status_id;
      civicrm_api3('Case', 'create', $case_params);
    }

    drupal_set_message(t('Your CV is successfully updated'));
    $form_state['redirect'] = 'portal';
  }
}

function candidate_expert_cv_get_forms(&$form_state, $currstep) {
  $return[0] = candidate_expert_cv_contact_details($form_state, $currstep == 0 ? true : false);
  $return[1] = candidate_expert_cv_additional_details($form_state, $currstep == 1 ? true : false);
  $return[2] = pum_expert_mycv_education_form($form_state, $currstep == 2 ? true : false);
  $return[3] = pum_expert_mycv_workhistory_form($form_state, $currstep == 3 ? true : false);
  $return[4] = candidate_expert_cv_code_of_conduct($form_state, $currstep == 4 ? true : false);

  return $return;
}

function candidate_expert_cv_code_of_conduct(&$form_state, $rebuild=false) {
  $contact = pum_expert_mycv_get_civi_contact();
  $form = array();

  $form['code_of_conduct']['#type'] = 'fieldset';
  $form['code_of_conduct']['#title'] = t('PUM Code of Conduct');

  $form['code_of_conduct']['info'] = array(
    '#type' => 'markup',
    '#markup' => t('PUM sets high standards as regard honesty, integrity and mutual respect for people and the environment. In order to join PUM as an expert we ask you to agree with our code of conduct by ticking the checkbox below. Once you have entered all your details (in English), please send this form to PUM by clicking the submit button. ')
  );

  $form['code_of_conduct']['link'] = array(
    '#type' => 'markup',
    '#markup' => '<p>'.l(t('Read code of conduct'), 'https://www.pum.nl/content/Basisvoorwaarden').'</p>',
  );

  $form['code_of_conduct']['code_of_conduct'] = array(
    '#type' => 'checkbox',
    '#title' => t('I agree to the Code of Conduct'),
  );

  return array('form' => $form, 'title' => t('Code of conduct'));
}

function candidate_expert_cv_additional_details(&$form_state, $rebuild=false) {
  $contact = pum_expert_mycv_get_civi_contact();
  $form = array();
  $form['medical_information']['#type'] = 'fieldset';
  $form['medical_information']['#title'] = t('Medical information');

  $form['medical_information']['health_insurance_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Health insurance company'),
    '#default_value' => $contact['Medical_Information::Health_Insurance_Company'],
  );

  $form['medical_information']['health_insurance_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Health insurance number'),
    '#default_value' => $contact['Medical_Information::Health_Insurance_Number'],
  );

  $form['medical_information']['foreign_health_insurance'] = array(
    '#type' => 'select',
    '#title' => t('Do you have a foreign Health Insurance Company '),
    '#options' => array('no' => t('No'), 'yes' => t('Yes')),
    '#default_value' => (!empty($contact['Medical_Information::Health_Insurance_Country']) && $contact['Medical_Information::Health_Insurance_Country'] != 1152) ? 'yes' : 'no',
  );

  $form['medical_information']['health_insurance_country'] = array(
    '#type' => 'select',
    '#title' => t('Health Insurance Country'),
    '#default_value' => !empty($contact['Medical_Information::Health_Insurance_Country']) ? $contact['Medical_Information::Health_Insurance_Country'] : 1152,
    '#options' => CRM_Core_PseudoConstant::country(),
    '#states' => array (
      'visible' => array(
        ':input[name="foreign_health_insurance"]' => array('value' => 'yes'),
      ),
    )
  );

  $form['bank_information']['#type'] = 'fieldset';
  $form['bank_information']['#title'] = t('Bank Account information');

  $form['bank_information']['bank_account_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Bank account number'),
    '#default_value' => $contact['Bank_Information::Bank_Account_Number'],
  );

  $form['bank_information']['iban_number'] = array(
    '#type' => 'textfield',
    '#title' => t('IBAN number'),
    '#default_value' => $contact['Bank_Information::IBAN_nummer'],
  );

  $form['bank_information']['bic'] = array(
    '#type' => 'textfield',
    '#title' => t('BIC / Swift code'),
    '#default_value' => $contact['Bank_Information::BIC_Swiftcode'],
  );

  $form['bank_information']['accountholder_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder name'),
    '#default_value' => $contact['Bank_Information::Accountholder_name'],
  );

  $form['bank_information']['foreign_bank'] = array(
    '#type' => 'select',
    '#title' => t('Do you have a foreign Bank Account'),
    '#options' => array('no' => t('No'), 'yes' => t('Yes')),
    '#default_value' => (!empty($contact['Bank_Information::Bank_Country_ISO_Code']) && $contact['Bank_Information::Bank_Country_ISO_Code'] != 1152) ? 'yes' : 'no',
  );

  $form['foreign_bank_information']['#type'] = 'fieldset';
  $form['foreign_bank_information']['#title'] = t('Information Foreign Bankaccount');
  $form['foreign_bank_information']['#states'] = array(
    'visible' => array(
      ':input[name="foreign_bank"]' => array('value' => 'yes'),
    ),
  );

  $form['foreign_bank_information']['bank_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bank name'),
    '#default_value' => $contact['Bank_Information::Bank_Name'],
  );

  $form['foreign_bank_information']['bank_city'] = array(
    '#type' => 'textfield',
    '#title' => t('Bank city'),
    '#default_value' => $contact['Bank_Information::Bank_City'],
  );

  $form['foreign_bank_information']['bank_country'] = array(
    '#type' => 'select',
    '#title' => t('Bank Country ISO Code'),
    '#default_value' => !empty($contact['Bank_Information::Bank_Country_ISO_Code']) ? $contact['Bank_Information::Bank_Country_ISO_Code'] : 1152,
    '#options' => CRM_Core_PseudoConstant::country(),
  );

  $form['foreign_bank_information']['accountholder_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder address'),
    '#default_value' => $contact['Bank_Information::Accountholder_address'],
  );

  $form['foreign_bank_information']['accountholder_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder postal code'),
    '#default_value' => $contact['Bank_Information::Accountholder_postal_code'],
  );

  $form['foreign_bank_information']['accountholder_city'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder city'),
    '#default_value' => $contact['Bank_Information::Accountholder_city'],
  );

  $form['foreign_bank_information']['accountholder_country'] = array(
    '#type' => 'select',
    '#title' => t('Accountholder country'),
    '#default_value' => !empty($contact['Bank_Information::Accountholder_country']) ? $contact['Bank_Information::Accountholder_country'] : 1152,
    '#options' => CRM_Core_PseudoConstant::country(),
  );

  $form['foreign_bank_information']['other_bank_information'] = array(
    '#type' => 'textarea',
    '#title' => t('Other Bank Information/Comments'),
    '#default_value' => $contact['Bank_Information::Other_Bank_Information_Comments'],
  );

  return array('form' => $form, 'title' => t('Additional details'));
}

function candidate_expert_cv_contact_details(&$form_state, $rebuild=false) {
  $contact = pum_expert_mycv_get_civi_contact();

  $form['contact_information']['#type'] = 'fieldset';
  $form['contact_information']['#title'] = t('Contact information');
  $form['contact_information']['prefix'] = array(
    '#type' => 'select',
    '#title' => t('Prefix'),
    '#options' => array('' => t('- None -')) + CRM_Core_OptionGroup::values('individual_prefix'),
    '#default_value' => $contact['prefix_id'],
  );
  $form['contact_information']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => $contact['first_name'],
  );
  $form['contact_information']['middle_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle name'),
    '#default_value' => $contact['middle_name'],
  );
  $form['contact_information']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => $contact['last_name'],
  );

  $form['contact_information']['initials'] = array(
    '#type' => 'textfield',
    '#title' => t('Initials'),
    '#default_value' => $contact['Additional_Data::Initials'],
  );

  $form['contact_information']['street_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#default_value' => $contact['home_address']['street_address'],
  );
  $form['contact_information']['postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => $contact['home_address']['postal_code'],
  );
  $form['contact_information']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $contact['home_address']['city'],
  );
  $countries = CRM_Core_PseudoConstant::country();
  $benelux = array();
  $benelux[1152] = $countries[1152]; //NL
  $benelux[1082] = $countries[1082]; //DE
  $benelux[1020] = $countries[1020]; //BE
  $benelux[1126] = $countries[1126]; //LU
  $form['contact_information']['country_id'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#default_value' => !empty($contact['home_address']['country_id']) ? $contact['home_address']['country_id'] : 1152,
    '#options' => $benelux,
  );

  $form['contact_information']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Home phone number'),
    '#default_value' => $contact['home_phone']['phone'],
    '#rules' => array(
      'phone_validation',
    )
  );
  $form['contact_information']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone number'),
    '#default_value' => $contact['mobile']['phone'],
    '#rules' => array(
      'phone_validation',
    )
  );
  $form['contact_information']['fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax number'),
    '#default_value' => $contact['fax']['phone'],
    '#rules' => array(
      'phone_validation',
    )
  );

  $form['contact_information']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => $contact['email']['email'],
    '#rules' => array(
      'email',
    ),
    '#required' => true,
  );

  $form['passport']['#type'] = 'fieldset';
  $form['passport']['#title'] = t('Passport information');

  $form['passport']['passport_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport name- First name(s)'),
    '#default_value' => $contact['Passport_Information::Passport_Name'],
  );
  $form['passport']['passport_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport name - Surname'),
    '#default_value' => $contact['Passport_Information::Passport_Name_Last_Name'],
  );
  $form['passport']['passport_partner_name'] = array(
    '#type' => 'textfield',
    '#title' => t('E / V (Partner Surname)'),
    '#default_value' => $contact['Passport_Information::Passport_Name_Partner_Last_Name'],
  );
  $form['passport']['passport_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport number'),
    '#default_value' => $contact['Passport_Information::Passport_Number'],
  );

  $form['passport']['passport_valid_until'] = array(
    '#type' => 'date_select',
    '#date_format' => 'Y-m-d',
    '#title' => t('Passport Expiry Date'),
    '#date_year_range' => '0:+10',
    //'#pre_render' => array('_pum_expert_cv_form_pre_render_date'),
    '#default_value' => _pum_expert_cv_form_date_string_value($contact['Passport_Information::Passport_Valid_until']),
  );

  $form['passport']['city_of_birth'] = array(
    '#type' => 'textfield',
    '#title' => t('City of birth'),
    '#default_value' => $contact['Additional_Data::City_of_Birth'],
  );

  $form['passport']['country_of_birth'] = array(
    '#type' => 'select',
    '#title' => t('Country of birth'),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#default_value' => !empty($contact['Additional_Data::Country_of_Birth']) ? $contact['Additional_Data::Country_of_Birth'] : 1152,
  );

  $form['passport']['nationality'] = array(
    '#type' => 'select',
    '#title' => t('Nationality'),
    '#options' => CRM_Core_OptionGroup::values('nationalities'),
    '#default_value' => !empty($contact['Nationality::Nationality']) ? $contact['Nationality::Nationality'] : 'Dutch',
  );

  $form['ice']['#type'] = 'fieldset';
  $form['ice']['#title'] = t('In Case of Emergency Contact');

  $form['ice']['ice_relationship'] = array(
    '#type' => 'select',
    '#title' => t('Relationship with contact'),
    '#options' => array('' => t(' -- None --')) + CRM_Core_OptionGroup::values('relationship_with_contact_20141119151423'),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::Relationship_with_contact'],
  );

  $form['ice']['ice_other'] = array(
    '#type' => 'textfield',
    '#title' => t('Please specify Other relationship'),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::Other_relationship'],
    '#states' => array(
      'visible' => array(
        ':input[name="ice_relationship"]' => array('value' => 'Other'),
      ),
    ),
  );

  $form['ice']['ice_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::First_name_contact'],
  );
  $form['ice']['ice_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::Last_name_contact'],
  );
  $form['ice']['ice_phone_1'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number 1'),
    '#rules' => array(
      'phone_validation',
    ),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::Phone_number_1'],
  );
  $form['ice']['ice_phone_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number 2'),
    '#rules' => array(
      'phone_validation',
    ),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::Phone_number_2'],
  );
  $form['ice']['ice_email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#rules' => array(
      'email',
    ),
    '#default_value' => $contact['In_Case_of_Emergency_Contact::Email_Address'],
  );

  return array('form' => $form, 'title' => t('Candidate expert'));
}