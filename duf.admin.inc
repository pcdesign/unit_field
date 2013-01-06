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
  $resultss= list_units();
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
 

//admin for new unit creation and editing

function duf_create_new_unit ($form, $form_state) {

$resultss = all_groups();
foreach ($resultss as $rows){
	$optionsg[$rows['group_id']]=$rows['groupname'];
}

$resultss = all_lists();
foreach ($resultss as $rows){
	$optionsl[$rows['list_id']]=$rows['listname'];
}
	
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
		   '#options' => $optionsg,
		   '#description' => t('Set this to the group you want to create. Leave blanck if you do not want a saperate group.'),
		   '#empty_value' => 'empty',
	 );
	$form['list'] = array(
		   '#type' => 'select',
		   '#title' => t('Select the correct list'),
		   '#options' => $optionsl,
		   '#description' => t('Set this to the list of unitgroups you want. Leave blanck if you do not want a saperate group.'),
		   '#required' => TRUE,
		   
	 );	
	 $form [] = array('#type' => 'submit', '#value' => t('Submit'));
	return $form;
}

function duf_edit_unit ($form, $form_state, $vars) {
	$resultss= list_units($vars);
  foreach ($resultss as $rowss){
	$options[$rowss['unit_id']] = array(
		'name' => $rowss['unitname_full'],
		'abbr' => $rowss['unitname_short'],
		'list' => $rowss['listname'],
		'groupname' => $rowss['groupname'],
		'editlink' => '<a href=' . $GLOBALS['base_url'] .'/admin/config/user-interface/duf/unit/'. $rowss['unit_id'] . '/edit/> edit </a>',
    );
}
$resultss = all_groups();
foreach ($resultss as $rows){
	$optionsg[$rows['group_id']]=$rows['groupname'];
}

$resultss = all_lists();
foreach ($resultss as $rows){
	$optionsl[$rows['list_id']]=$rows['listname'];
}
	$form['unit_id'] = array('#type' => 'value', '#value' => $rowss['unit_id']);
	 $form['element_container'] = array(
		'#type' => 'fieldset',
		'#title' => t('Edit unit:'),
		'#description' => t('Add a new unit to you database / '),
		'#collapsible' => FALSE,
	);
	$form ['unitname'] = array ( 
		'#type' => 'textfield',
		'#title' => t('Unit name in full'),
		'#description' => t('e.g. kilo or gallon'),
		'#required' => TRUE,
		'#default_value' => $rowss['unitname_full'], 
	);
	$form ['unit_abbriviated'] = array ( 
		'#type' => 'textfield',
		'#title' => t('Unit name abbreviated'),
		'#description' => t('e.g. kg or gal'),
		'#required' => TRUE,
		'#default_value' => $rowss['unitname_short'], 
	);
	$form['unitgroups'] = array(
	   '#type' => 'select',
	   '#title' => t('Select the group'),
	   '#options' => $optionsg,
	   '#description' => t('Set this to the group you want to create. Leave blanck if you do not want a saperate group.'),
	   '#empty_value' => 'empty',
		'#default_value' => $rowss['group_id'], 

	 );
	$form['list'] = array(
	   '#type' => 'select',
	   '#title' => t('Select the correct list'),
	   '#options' => $optionsl,
	   '#description' => t('Set this to the list of unitgroups you want. Leave blanck if you do not want a saperate group.'),
	   '#required' => TRUE,
		'#default_value' => $rowss['list_id'], 
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
}
function duf_edit_unit_submit($form, &$form_state) {
	$query = db_update('duf_unit')
	  ->fields(array(
		'unitname_full' => $form_state['values']['unitname'],
		'unitname_short' => $form_state['values']['unit_abbriviated'],
		'groupid' => 1,
	  ))
	  ->condition('unit_id', $form_state['values']['unit_id'])
	  ->execute();
		$form_state['redirect'] = 'admin/config/user-interface/duf';

	  drupal_set_message(t('Your unit has been updated.'));
}

/* 
list of active groups
*/


function duf_list_groups ($form, $form_state) {
	$form['groups'] = array(
		'#type' => 'fieldset',
		'#title' => t('View the active groups'),
		'#description' => t('List of all active groups.'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
		'#tree' => TRUE,
	  );
	 
	  //make header title for table
	  $header= array(
		'name' => 'groupname',
		'list' => 'List',
		'editlink' => 'Edit',
		);
	//prepare the optionlist for the table
	  $resultss= all_groups();
	  foreach ($resultss as $rowss){
		$options[$rowss['group_id']] = array(
			'name' => $rowss['groupname'],
			'list' => $rowss['listname'],
			'editlink' => '<a href=' . $GLOBALS['base_url'] .'/admin/config/user-interface/duf/group/'. $rowss['group_id'] . '/edit/> edit </a>',
		);
	}
	$form['groups']['list'] = array(
		  '#type' => 'tableselect',
		  '#header' => $header,
		  '#options' => $options,
		);

	 return $form;
 }
 
 
function duf_edit_group ($form, $form_state, $vars) {
	$resultss= all_groups($vars);
  foreach ($resultss as $rowss){
	$options[$rowss['group_id']] = array(
		'name' => $rowss['groupname'],
		'list' => $rowss['listname'],
		'list_id'=> $rowss['list_id'],
		'editlink' => '<a href=' . $GLOBALS['base_url'] .'/admin/config/user-interface/duf/unit/'. $rowss['group_id'] . '/edit/> edit </a>',
    );
}
$resultss = all_lists();
foreach ($resultss as $rows){
	$optionsl[$rows['list_id']]=$rows['listname'];
}
	$form['group_id'] = array('#type' => 'value', '#value' => $rowss['group_id']);
	 $form['element_container'] = array(
		'#type' => 'fieldset',
		'#title' => t('Edit group: ' . $rows['groupname']),
		'#description' => t('Edit the group details '),
		'#collapsible' => FALSE,
	);
	$form ['groupname'] = array ( 
		'#type' => 'textfield',
		'#title' => t('Unit name in full'),
		'#description' => t('e.g. kilo or gallon'),
		'#required' => TRUE,
		'#default_value' => $rowss['groupname'], 
	);
	$form['list'] = array(
	   '#type' => 'select',
	   '#title' => t('Select the correct list'),
	   '#options' => $optionsl,
	   '#description' => t('Set this to the list of unitgroups you want. Leave blanck if you do not want a saperate group.'),
	   '#required' => TRUE,
		'#default_value' => $rowss['list_id'], 
	 );	
	 $form [] = array('#type' => 'submit', '#value' => t('Submit'));
	return $form;
}

function duf_edit_group_submit($form, &$form_state) {
	$query = db_update('duf_groups')
	  ->fields(array(
		'groupname' => $form_state['values']['groupname'],
		'listid' => $form_state['values']['list'],
	  ))
	  ->condition('group_id', $form_state['values']['group_id'])
	  ->execute();
		$form_state['redirect'] = 'admin/config/user-interface/duf/group';

	  drupal_set_message(t('Your unit has been updated.'));
}
/*
list of data functions
*/

function all_groups ($group=''){
$sql = 'SELECT g.groupname, l.listname, g.group_id, l.listname, l.list_id
		FROM   {duf_groups} g 
		LEFT JOIN {duf_lists}  l ON g.listid = l.list_id
		WHERE TRUE ';
			if ($group != ''){
		$sql = $sql .' AND g.group_id =' . $group;
	}
		$sql= $sql .' ORDER BY g.groupname ASC';
	$result = db_query($sql);

	if ($result->rowCount() > 0){ 
	  while($row = $result->fetchAssoc()) {
		$results[]=$row;
	  }
	}
	 return $results;
}

function all_lists ($list='') {
$sql = 'SELECT l.listname, l.list_id, g.group_id, g.groupname
		FROM   {duf_lists} l LEFT JOIN 
		{duf_groups} g ON l.list_id = g.listid
		WHERE TRUE ';
	if ($list != ''){
		$sql = $sql .' AND l.list_id =' . $list;
	}		
	$sql= $sql .' ORDER BY l.listname ASC';
	$result = db_query($sql);

	if ($result->rowCount() > 0){ 
	  while($row = $result->fetchAssoc()) {
		$results[]=$row;
	  }
	}
	return $results;
}

function list_units ($unit='') {
	$sql = 'SELECT u.unit_id, u.unitname_full, u.unitname_short, g.groupname, l.listname, g.group_id, l.listname, l.list_id
		FROM  {duf_unit} u
		  INNER JOIN {duf_groups} g ON u.groupid = g.group_id
		  INNER JOIN {duf_lists}  l ON g.listid = l.list_id
		WHERE TRUE';
	if ($unit != ''){
		$sql = $sql .' AND u.unit_id =' . $unit;
	}
	$sql= $sql . ' ORDER BY u.unitname_full ASC ';
	$result = db_query($sql);

	if ($result->rowCount() > 0){ 
	  while($row = $result->fetchAssoc()) {
		$results[]=$row;
	  }
	}
	 return $results;
}