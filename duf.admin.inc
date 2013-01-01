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
    '#collapsed' => FALSE,
	'#tree' => TRUE,
  );
 
  //make header title for table
  $header= array(
	'name' => 'Unitname',
	'abbr' => 'Unit abbr.',
	'group' => 'Group',
	'list' => 'List',
	'editlink' => 'Edit',
	);
//prepare the optionlist for the table
  $resultss= list_all_units();
  foreach ($resultss as $rowss){
	$options[$rowss['unit_id']] = array(
		'name' => $rowss['unitname_full'],
		'abbr' => $rowss['unitname_short'],
		'group' => $rowss['groupname'],
		'list' => $rowss['listname'],
		'editlink' => '<a href=' . $GLOBALS['base_url'] .'/admin/config/user-interface/duf/unit/'. $rowss['unit_id'] . '/edit/> edit </a>',
    );
}
$form['units']['list'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
    );

  return $form;

 
 
 }
 

//admin for new unit creation

function duf_create_new_unit ($form, $form_state) {
	
	 $form['element_container'] = array(
		'#type' => 'fieldset',
		'#title' => t('Add a new unit'),
		'#description' => t('Add a new unit to you database'),
		'#collapsible' => FALSE,
	);
	$form ['unitname'] = array ( 
		'#type' => 'textfield',
		'#title' => t('Unit name in full'),
		'#description' => t('e.g. kilo or gallon'),
		'#required' => TRUE,
	);
	$form ['unit_abbriviated'] = array ( 
		'#type' => 'textfield',
		'#title' => t('Unit name abbreviated'),
		'#description' => t('e.g. kg or gal'),
		'#required' => TRUE,
	);
	$form['unitgroups'] = array(
		   '#type' => 'select',
		   '#title' => t('Select the group'),
		   '#options' => all_groups(),
		   '#description' => t('Set this to the group you want to create. Leave blanck if you do not want a saperate group.'),
		   '#empty_value' => 'empty',
	 );
	$form['list'] = array(
		   '#type' => 'select',
		   '#title' => t('Select the correct list'),
		   '#options' => all_lists(),
		   '#description' => t('Set this to the list of unitgroups you want. Leave blanck if you do not want a saperate group.'),
		   '#required' => TRUE,
		   
	 );	
	 $form [] = array('#type' => 'submit', '#value' => t('Submit'));
	return $form;
}

function duf_create_new_unit_validate($form, &$form_state) {
  if ($form_state['values']['unitname'] == '') {
    form_set_error('d', t('You must select a name for this group of settings.' ));
  }
}

function duf_create_new_unit_submit($form, &$form_state) {
$query = db_insert('duf_unit')
  ->fields(array(
    'unitname_full' => $form_state['values']['unitname'],
    'unitname_short' => $form_state['values']['unit_abbriviated'],
    'groupid' => 1,
  ))
  ->execute();
  drupal_set_message(t('Your unit has been saved.'));
  drupal_set_message( print_r(list_all_units()));
}

// list of active units
function list_all_units () {
$sql = 'SELECT u.unit_id, u.unitname_full, u.unitname_short, g.groupname, l.listname
    FROM  {duf_unit} u
      INNER JOIN {duf_groups} g ON u.groupid = g.group_id
	  INNER JOIN {duf_lists}  l ON g.listid = l.list_id
    WHERE TRUE
    ORDER BY u.unitname_full DESC
  ';
$result = db_query($sql);

if ($result->rowCount() > 0){ 
  while($row = $result->fetchAssoc()) {
	$results[]=$row;
  }
}
  return $results;
}

/*
list of reuseable functions
*/

function all_groups (){
	$groups = array('g1','g2'); 
	return $groups;
}

function all_lists () {
	$lists = array ('l1','l2');
	return $lists;
}