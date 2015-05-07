<?php

require_once('civicrm.inc');
require_once('education.inc');
require_once('workhistory.inc');

function candidate_expert_cv($form, &$form_state) {

  if(!isset($form_state['step'])) {
    $form_state['step'] = 0;
  }
  $current_step = $form_state['step'];

  $step_count = candidate_expert_cv_get_form_count();
  $current_form = candidate_expert_cv_get_form($form_state, $current_step, $step_count);

  $return['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>'.$current_form['title'].' ('.($current_step+1).'/'.$step_count.')</h2>',
  );
  $return['form'] =  $current_form['form'];

  $path = drupal_get_path('module', 'pum_portal_webform_help');
  drupal_add_js($path . '/ppwh.js');
  drupal_add_css($path . '/ppwh.css');

  return $return;
}

function candidate_expert_cv_validate($form, &$form_state) {
  if (form_get_errors()) {
    $path = drupal_get_path('module', 'pum_portal_webform_help');
    drupal_add_js($path . '/ppwh.js');
    drupal_add_css($path . '/ppwh.css');
  }
}

function candidate_expert_cv_get_form_count() {
  return 5;
}

function candidate_expert_cv_get_form(&$form_state, $current_step, $step_count) {
  switch($current_step) {
    case 0:
      return candidate_expert_cv_contact_details($form_state);
      break;
    case 1:
      return candidate_expert_cv_additional_details($form_state);
      break;
    case 2:
      return pum_expert_mycv_education_form($form_state, 'candidate_expert_cv');
      break;
    case 3:
      return pum_expert_mycv_workhistory_form($form_state, 'candidate_expert_cv');
      break;
    case 4:
      return candidate_expert_cv_code_of_conduct($form_state);
      break;
  }

  throw new Exception('Current step in form not found');
}

function candidate_expert_cv_validate_foreign_bank($form, &$form_state) {
  if (!empty($form_state['values']['foreign_bank']) && $form_state['values']['foreign_bank'] == 'yes') {
    if (empty($form_state['values']['bank_name'])) {
      form_set_error('bank_name','Bank name is required');
    }
    if (empty($form_state['values']['bank_city'])) {
      form_set_error('bank_city','Bank city is required');
    }
    if (empty($form_state['values']['bank_country']) || $form_state['values']['bank_country'] == 1152) {
      form_set_error('bank_country', t('Bank Country ISO Code is required'));
    }
    if (empty($form_state['values']['accountholder_address'])) {
      form_set_error('accountholder_address','Accountholder address is required');
    }
    if (empty($form_state['values']['accountholder_postal_code'])) {
      form_set_error('accountholder_postal_code','Accountholder postal code is required');
    }
    if (empty($form_state['values']['accountholder_city'])) {
      form_set_error('accountholder_city','Accountholder City is required');
    }
    if (empty($form_state['values']['accountholder_country']) || $form_state['values']['accountholder_country'] == 1152) {
      form_set_error('accountholder_country', t('Accountholder Country ISO Code is required'));
    }
  }

  $path = drupal_get_path('module', 'pum_portal_webform_help');
  drupal_add_js($path . '/ppwh.js');
  drupal_add_css($path . '/ppwh.css');
}

function candidate_expert_cv_validate_foreign_insurance($form, &$form_state) {
  if (!empty($form_state['values']['foreign_health_insurance']) && $form_state['values']['foreign_health_insurance'] == 'yes') {
    if (empty($form_state['values']['health_insurance_country']) || $form_state['values']['health_insurance_country'] == 1152) {
      form_set_error('health_insurance_country', t('Health insurance country is required'));
    }
  }

  $path = drupal_get_path('module', 'pum_portal_webform_help');
  drupal_add_js($path . '/ppwh.js');
  drupal_add_css($path . '/ppwh.css');
}

function candidate_expert_cv_validate_code_of_conduct($form, &$form_state) {
  if (empty($form_state['values']['code_of_conduct'])) {
    form_set_error('code_of_conduct', t('You didn\'t agree to the Code of Conduct'));
  }

  $path = drupal_get_path('module', 'pum_portal_webform_help');
  drupal_add_js($path . '/ppwh.js');
  drupal_add_css($path . '/ppwh.css');
}

function candidate_expert_cv_previous($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['input'];
  $form_state['step'] = $form_state['step'] - 1;
  $form_state['values'] = $form_state['storedvalues'][$form_state['step']];
  $form_state['next'] = false;
  $form_state['previous'] = true;
  $form_state['rebuild'] = TRUE;
}

function candidate_expert_cv_next($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  $form_state['step'] = $form_state['step'] + 1;
  if (isset($form_state['storedvalues'][$form_state['step']])) {
    $form_state['values'] = $form_state['storedvalues'][$form_state['step']];
  }
  $form_state['next'] = true;
  $form_state['previous'] = false;
  $form_state['rebuild'] = TRUE;
}

function candidate_expert_cv_code_of_conduct(&$form_state) {
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

  $form['code_of_conduct']['description'] = array(
    '#type' => 'markup',
    '#markup' => '<p>Make sure you have checked all your details before submitting this form.</p>',
  );

  $form['previous']['#type'] = 'submit';
  $form['previous']['#value'] = t('Previous');
  $form['previous']['#submit'] = array('candidate_expert_cv_previous');
  $form['previous']['#limit_validation_errors'] = array();
  $form['previous']['#validate'] = array();

  $form['next']['#type'] = 'submit';
  $form['next']['#value'] = t('Submit');
  $form['next']['#validate'][] ='candidate_expert_cv_validate_code_of_conduct';

  return array('form' => $form, 'title' => t('Code of conduct'));
}

function candidate_expert_cv_additional_details(&$form_state) {
  $contact = pum_expert_mycv_get_civi_contact();

  $values = array();
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  $form = array();
  $form['medical_information']['#type'] = 'fieldset';
  $form['medical_information']['#title'] = t('Medical information');

  $form['medical_information']['health_insurance_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Health insurance company'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'health_insurance_company', 'Medical_Information::Health_Insurance_Company'),
    '#required' => true,
  );

  $form['medical_information']['health_insurance_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Health insurance number'),
    '#default_value' => $contact['Medical_Information::Health_Insurance_Number'],
    '#default_value' => pum_expert_mycv_value($values, $contact, 'health_insurance_number', 'Medical_Information::Health_Insurance_Number'),
    '#required' => true,
  );

  $contact['Medical_Information::Health_Insurance_Country_Selected'] = (!empty($contact['Medical_Information::Health_Insurance_Country']) && $contact['Medical_Information::Health_Insurance_Country'] != 1152) ? 'yes' : 'no';
  $form['medical_information']['foreign_health_insurance'] = array(
    '#type' => 'select',
    '#title' => t('Do you have a foreign Health Insurance Company '),
    '#options' => array('no' => t('No'), 'yes' => t('Yes')),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'foreign_health_insurance', 'Medical_Information::Health_Insurance_Country_Selected'),
  );

  $form['medical_information']['health_insurance_country'] = array(
    '#type' => 'select',
    '#title' => t('Health Insurance Country'),
    '#field_suffix' => '<p class="description">If you have foreign health insurance, please specify the country. In the case of foreign health insurance, for each foreign journey on behalf of PUM, you will be required to take out travel insurance from your place of residence to the Netherlands.</p>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'health_insurance_country', 'Medical_Information::Health_Insurance_Country', '', 1152),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#states' => array (
      'visible' => array(
        ':input[name="foreign_health_insurance"]' => array('value' => 'yes'),
      ),
      'required' => array(
        ':input[name="foreign_health_insurance"]' => array('value' => 'yes'),
      ),
    )
  );

  $form['bank_information']['#type'] = 'fieldset';
  $form['bank_information']['#title'] = t('Bank Account information');

  $form['bank_information']['bank_account_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Bank account number'),
    '#field_suffix' => '<code class="help">Account number for the account holder in figures.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'bank_account_number', 'Bank_Information::Bank_Account_Number'),
    '#required' => true,
    '#rules' => array(
      'numeric',
    ),
  );

  $form['bank_information']['iban_number'] = array(
    '#type' => 'textfield',
    '#title' => t('IBAN number'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'iban_number', 'Bank_Information::IBAN_nummer'),
    '#required' => true,
  );

  $form['bank_information']['bic'] = array(
    '#type' => 'textfield',
    '#title' => t('BIC / Swift code'),
    '#field_suffix' => '<code class="help">always 11 numbers/figures. If the code consists of a smaller number, complete the code with the letter ‘X’, ‘XX’ or ‘XXX’ until you have reached 11 characters.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'bic', 'Bank_Information::BIC_Swiftcode'),
    '#required' => true,
  );

  $form['bank_information']['accountholder_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder name'),
    '#field_suffix' => '<code class="help">The precise name of the account holder. This must be identical to the name known to the bank.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'accountholder_name', 'Bank_Information::Accountholder_name'),
    '#required' => true,
  );

  $contact = (!empty($contact['Bank_Information::Bank_Country_ISO_Code']) && $contact['Bank_Information::Bank_Country_ISO_Code'] != 1152) ? 'yes' : 'no';
  $form['bank_information']['foreign_bank'] = array(
    '#type' => 'select',
    '#title' => t('Do you have a foreign Bank Account'),
    '#field_suffix' => '<code class="help">If No, please continue. If Yes, please complete the extra information fields concerning your foreign account.</code>',
    '#options' => array('no' => t('No'), 'yes' => t('Yes')),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'foreign_bank', 'Bank_Information::Bank_Country_ISO_Code_Selected'),
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
    '#field_suffix' => '<code class="help">Name of the bank (max 50 characters, no new lines / line breaks permitted here) The bank name is mandatory for non-Dutch banks.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'bank_name', 'Bank_Information::Bank_Name'),
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
        ),
    ),
  );

  $form['foreign_bank_information']['bank_city'] = array(
    '#type' => 'textfield',
    '#title' => t('Bank city'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'bank_city', 'Bank_Information::Bank_City'),
    '#field_suffix' => '<code class="help">City where the bank is located. (max 50 characters, no new lines / line breaks permitted here). The bank city is mandatory for non-Dutch banks.</code>',
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
      ),
    ),
  );

  $form['foreign_bank_information']['bank_country'] = array(
    '#type' => 'select',
    '#title' => t('Bank Country ISO Code'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'bank_country', 'Bank_Information::Bank_Country_ISO_Code', '', 1152),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
      ),
    ),
  );

  $form['foreign_bank_information']['accountholder_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder address'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'accountholder_address', 'Bank_Information::Accountholder_address'),
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
      ),
    ),
  );

  $form['foreign_bank_information']['accountholder_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder postal code'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'accountholder_postal_code', 'Bank_Information::Accountholder_postal_code'),
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
      ),
    ),
  );

  $form['foreign_bank_information']['accountholder_city'] = array(
    '#type' => 'textfield',
    '#title' => t('Accountholder city'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'accountholder_city', 'Bank_Information::Accountholder_city'),
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
      ),
    ),
  );

  $form['foreign_bank_information']['accountholder_country'] = array(
    '#type' => 'select',
    '#title' => t('Accountholder country'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'accountholder_country', 'Bank_Information::Accountholder_country', '', 1152),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#states' => array (
      'required' => array(
        ':input[name="foreign_bank"]' => array('value' => 'yes'),
      ),
    ),
  );

  $form['foreign_bank_information']['other_bank_information'] = array(
    '#type' => 'textarea',
    '#title' => t('Other Bank Information/Comments'),
    '#field_suffix' => '<code class="help">Please add any comments relevant to payment, account holder, bank information, or payment address information</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'other_bank_information', 'Bank_Information::Other_Bank_Information_Comments'),

  );

  $form['previous']['#type'] = 'submit';
  $form['previous']['#value'] = t('Previous');
  $form['previous']['#submit'] = array('candidate_expert_cv_previous');
  $form['previous']['#limit_validation_errors'] = array();
  $form['previous']['#validate'] = array();

  $form['next']['#type'] = 'submit';
  $form['next']['#value'] = t('Next');
  $form['next']['#submit'] = array('candidate_expert_cv_next');
  $form['next']['#validate'][] ='candidate_expert_cv_validate_foreign_insurance';
  $form['next']['#validate'][] ='candidate_expert_cv_validate_foreign_bank';

  return array('form' => $form, 'title' => t('Additional details'));
}

function candidate_expert_cv_contact_details(&$form_state) {
  $contact = pum_expert_mycv_get_civi_contact();
  $values = array();
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  $form['contact_information']['#type'] = 'fieldset';
  $form['contact_information']['#title'] = t('Contact information');
  $form['contact_information']['prefix'] = array(
    '#type' => 'select',
    '#title' => t('Prefix'),
    '#options' => array('' => t('- None -')) + CRM_Core_OptionGroup::values('individual_prefix'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'prefix', 'prefix_id'),
    '#required' => true,
  );
  $form['contact_information']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#field_suffix' => '<code class="help">this is the name according to which you are registered in the system at PUM. It is the name according to which we will approach you.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'first_name', 'first_name'),
    '#required' => true,
  );
  $form['contact_information']['middle_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Infix'),
    '#field_suffix' => '<code class="help">de, het, van de, etc.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'middle_name', 'middle_name'),
  );
  $form['contact_information']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'last_name', 'last_name'),
    '#required' => true,
  );

  $form['contact_information']['initials'] = array(
    '#type' => 'textfield',
    '#title' => t('Initials'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'initials', 'Additional_Data::Initials'),
    '#required' => true,
  );

  $form['contact_information']['street_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#default_value' => pum_expert_mycv_value($values, $contact['home_address'], 'street_address', 'street_address'),
    '#required' => true,
  );
  $form['contact_information']['postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => pum_expert_mycv_value($values, $contact['home_address'], 'postal_code', 'postal_code'),
    '#required' => true,
  );
  $form['contact_information']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => pum_expert_mycv_value($values, $contact['home_address'], 'city', 'city'),
    '#required' => true,
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
    '#field_suffix' => '<p class="description">PUM only includes experts in its database who are resident in the Netherlands. In consultation with the sector coordinator and Head of HRM, exceptions may be made in specific cases, for border areas in Belgium and Germany.</p>',
    '#default_value' => pum_expert_mycv_value($values, $contact['home_address'], 'country_id', 'country_id', '', 1152),
    '#options' => $benelux,
    '#required' => true,
  );

  $form['contact_information']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Home phone number'),
    '#default_value' => pum_expert_mycv_value($values, $contact['home_phone'], 'phone', 'phone'),
    '#field_suffix' => '<code class="help">For example: +31 50 1234567 or +31 6 12345678</code> <p class="description">In case of no other telephone than your mobile phone, please enter your mobile phone number here</p>',
    '#rules' => array(
      'phone_validation',
    ),
    '#required' => true,
  );
  $form['contact_information']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone number'),
    '#default_value' => pum_expert_mycv_value($values, $contact['mobile'], 'phone', 'phone'),
    '#rules' => array(
      'phone_validation',
    )
  );
  $form['contact_information']['fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax number'),
    '#default_value' => pum_expert_mycv_value($values, $contact['fax'], 'phone', 'phone'),
    '#rules' => array(
      'phone_validation',
    )
  );

  $form['contact_information']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => pum_expert_mycv_value($values, $contact['email'], 'email', 'email'),
    '#rules' => array(
      'email',
    ),
    '#required' => true,
  );

  $form['passport']['#type'] = 'fieldset';
  $form['passport']['#title'] = t('Passport information');
  $form['passport']['#description'] = 'In connection with booking tickets, we will need your full name as appearing in your passport.';

  $form['passport']['passport_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport name- First name(s)'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_first_name', 'Passport_Information::Passport_Name'),
    '#required' => true,
  );
  $form['passport']['passport_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport name - Surname'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_last_name', 'Passport_Information::Passport_Name_Last_Name'),
    '#required' => true,
  );
  $form['passport']['passport_partner_name'] = array(
    '#type' => 'textfield',
    '#title' => t('E / V (Partner Surname)'),
    '#field_suffix' => '<code class="help">If you have no married name, you are not required to complete this field.</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_partner_name', 'Passport_Information::Passport_Name_Partner_Last_Name'),
  );
  $form['passport']['passport_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport number'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_number', 'Passport_Information::Passport_Number'),
    '#required' => true,
  );

  $form['passport']['passport_valid_until'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d',
    '#title' => t('Passport Expiry Date'),
    '#date_year_range' => '0:+10',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_valid_until', 'Passport_Information::Passport_Valid_until', 'date'),
    '#required' => true,
  );

  $form['passport']['passport_place_of_issue'] = array(
    '#type' => 'textfield',
    '#title' => t('Passport Place of Issue'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_place_of_issue', 'Passport_Information::Passport_Place_of_Issue'),
    '#required' => true,
  );

  $form['passport']['passport_issue_date'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d',
    '#title' => t('Passport Issue Date'),
    '#date_year_range' => '0:+10',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'passport_issue_date', 'Passport_Information::Passport_Issue_Date', 'date'),
    '#required' => true,
  );

  $form['passport']['city_of_birth'] = array(
    '#type' => 'textfield',
    '#title' => t('City of birth'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'city_of_birth', 'Additional_Data::City_of_Birth'),
  );

  $form['passport']['country_of_birth'] = array(
    '#type' => 'select',
    '#title' => t('Country of birth'),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'country_of_birth', 'Additional_Data::Country_of_Birth', '', 1152),
  );

  $form['passport']['nationality'] = array(
    '#type' => 'select',
    '#title' => t('Nationality'),
    '#options' => CRM_Core_OptionGroup::values('nationalities'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'nationality', 'Nationality::Nationality', '', 'Dutch'),
    '#required' => true,
  );

  $form['ice']['#type'] = 'fieldset';
  $form['ice']['#title'] = t('In Case of Emergency Contact');

  $form['ice']['ice_relationship'] = array(
    '#type' => 'select',
    '#title' => t('Relationship with contact'),
    '#options' => array('' => t(' -- None --')) + CRM_Core_OptionGroup::values('relationship_with_contact_20141119151423'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_relationship', 'In_Case_of_Emergency_Contact::Relationship_with_contact'),
  );

  $form['ice']['ice_other'] = array(
    '#type' => 'textfield',
    '#title' => t('Please specify Other relationship'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_other', 'In_Case_of_Emergency_Contact::Other_relationship'),
    '#states' => array(
      'visible' => array(
        ':input[name="ice_relationship"]' => array('value' => 'Other'),
      ),
    ),
  );

  $form['ice']['ice_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_first_name', 'In_Case_of_Emergency_Contact::First_name_contact'),
    '#required' => true,
  );
  $form['ice']['ice_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_last_name', 'In_Case_of_Emergency_Contact::Last_name_contact'),
    '#required' => true,
  );
  $form['ice']['ice_phone_1'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number 1'),
    '#rules' => array(
      'phone_validation',
    ),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_phone_1', 'In_Case_of_Emergency_Contact::Phone_number_1'),
    '#required' => true,
  );
  $form['ice']['ice_phone_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number 2'),
    '#rules' => array(
      'phone_validation',
    ),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_phone_2', 'In_Case_of_Emergency_Contact::Phone_number_2'),
  );
  $form['ice']['ice_email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#rules' => array(
      'email',
    ),
    '#default_value' => pum_expert_mycv_value($values, $contact, 'ice_email', 'In_Case_of_Emergency_Contact::Email_Address'),
    '#required' => true,
  );

  $form['next']['#type'] = 'submit';
  $form['next']['#value'] = t('Next');
  $form['next']['#submit'] = array('candidate_expert_cv_next');

  return array('form' => $form, 'title' => t('Candidate expert'));
}

function candidate_expert_cv_submit($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  $form_state['next'] = false;
  $form_state['previous'] = false;

  civicrm_initialize();

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
  $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Place_of_Issue')] = $form_state['storedvalues'][0]['passport_place_of_issue'];
  $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Passport_Information::Passport_Issue_Date')] = _pum_expert_cv_form_date_submitted_string_value($form_state['storedvalues'][0]['passport_issue_date']);

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
