<?php

/**
 * @file
 *
 * @author greenSkin
 */

/*******************************************************************************
 * Callback Functions, Forms, and Tables
 ******************************************************************************/

/**
 * Settings form for module filter.
 */
function duf_settings() {
  $form['units'] = array(
    '#type' => 'fieldset',
    '#title' => t('View the active units'),
    '#description' => t('List of all active units.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
 
  $form['tabs']['module_filter_dynamic_save_position'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save dynamic positioning'),
    '#description' => t("DEVELOPMENTAL: For sites with lots of tabs, enable to help keep the 'Save configuration' button more accessible."),
    '#default_value' => variable_get('module_filter_dynamic_save_position', 0)
  );
  return system_settings_form($form);

 
 
 }
function duf_settings2 (){
  $form['units'] = array(
    '#type' => 'fieldset',
    '#title' => t('View the units'),
    '#description' => t('List of all active units.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
}