<?php
/*
 * @file
 * Common Functions
 *
 */

// check current status of practice (user) 
function qpp_check_status($pid){
	$status = '';
	if($pid){
		$practice = user_load($pid);
		if(isset($practice->field_practice_status['und'])){
			$status = $practice->field_practice_status['und'][0]['tid'];
		}
	}
	return $status;
}

function qpp_update_status($pid, $status){
	if($pid && $status){
		$practice = user_load($pid);
		$practice_wrapper = entity_metadata_wrapper('user', $practice);
		$practice_wrapper->field_practice_status->set($status);
		$practice_wrapper->save();
	}
}

// Set Grant SDO field value
function qpp_set_grant_sdo($pid){
	if($pid){
		$practice = user_load($pid);
		if(isset($practice->field_state_terms['und'])){
			$state_tid = $practice->field_state_terms['und'][0]['tid'];
		}	
		$state = taxonomy_term_load($state_tid);
		$sdo = $state->field_grant_sdo['und'][0]['target_id'];
		if($sdo){
			$practice = user_load($pid);
			$practice_wrapper = entity_metadata_wrapper('user', $practice);
			$practice_wrapper->field_grant_sdo->set($sdo);
			$practice_wrapper->save();
		}
	}
}

// check residence State of Practice [DO NOT DELETE]
function qpp_check_practice_state($pid){
	$state = '';
		if($pid){
			$practice = user_load($pid);
			if(isset($practice->field_state_terms['und'])){
				$state = $practice->field_state_terms['und'][0]['tid'];
			}		
		}	
	return qpp_set_term_name($state);
}

// check Grant SDO of Practice
function qpp_check_grant_sdo($pid){
	$sdo = '';
		if($pid){
			$practice = user_load($pid);
			if(isset($practice->field_grant_sdo['und'])){
				$sdo = $practice->field_grant_sdo['und'][0]['target_id'];
			}		
		}	
	return qpp_set_term_name($sdo);
}

// check Commercial SDO of Practice
function qpp_check_commercial_sdo($pid){
	$sdo = '';
		if($pid){
			$practice = user_load($pid);
			if(isset($practice->field_commercial_sdo['und'])){
				$sdo = $practice->field_commercial_sdo['und'][0]['target_id'];
			}		
		}	
	return qpp_set_term_name($sdo);
}

// check participating State(s) for QPP Advisors and Admins
function qpp_check_participating_state($uid){
	$participating_states = array();
	if($uid){
		$user = user_load($uid);
		if(isset($user->field_participating_states['und'])){
			foreach($user->field_participating_states['und'] as $value){
				$participating_states[] = qpp_set_term_name($value['tid']);	
			}
		}	
	}		
	return $participating_states;
}

// check grant SDO(s) for QPP Advisors and Admins
function qpp_check_sdo_assigned($uid){
	$sdos = array();
	if($uid){
		$user = user_load($uid);
		if(isset($user->field_sdo['und'])){
			foreach($user->field_sdo['und'] as $value){
				$sdos[$value['tid']] = qpp_set_term_name($value['tid']);	
			}
		}	
	}		
	return $sdos;
}

// check commercial sdo contract type
function qpp_check_commercial_sdo_contract_type(){
	$contract_type = array();
	global $user; // get logged in use
	$sdos = qpp_check_sdo_assigned($user->uid); //load SDOs for QPP Advisor
	if(isset($sdos) && !empty($sdos)){
		$vid = taxonomy_vocabulary_machine_name_load('commercial_contract_type')->vid;
		$vocab = taxonomy_term_load_multiple(array(), array('vid' => $vid));
		foreach($sdos as $sdo_tid => $sdo_term){
			foreach($vocab as $ct_tid => $ct_value){
				$sdo = taxonomy_term_load($ct_tid)->field_sdo_contract['und'][0]['target_id'];
				if($sdo_tid == $sdo){
					$contract_type[$ct_tid] = qpp_set_term_name($ct_tid);
				}
			}
		}	
	}
	return $contract_type;
}

// check sdo type Grant, Commercial or Both
function qpp_check_sdo_type($sdoid){
	$sdo_type = '';
	if($sdoid && !empty($sdoid)){
		$sdo = taxonomy_term_load($sdoid);
		if(isset($sdo) && isset($sdo->field_sdo_type['und'])){
			foreach($sdo->field_sdo_type['und'] as $value){
				$sdo_types[] = qpp_set_term_name($value['tid']);
			}
			if(in_array('Grant', $sdo_types) && in_array('Commercial', $sdo_types)){
				$sdo_type = 'All';
			}else if(in_array('Grant', $sdo_types)){
				$sdo_type = 'Grant';
			}else if(in_array('Commercial', $sdo_types)){
				$sdo_type = 'Commercial';
			}
		}
	}
	return $sdo_type;
}

// QPP check point
function qpp_check_point($pid){
	global $user; // get logged in user
	$practice = user_load($pid); // load user details of supplied id
	// check if logged in user is Practice
	if($pid && in_array('Practice', $user->roles)){
		// check if the page being viewed refers to the id supplied
		if($pid == $user->uid){
			return TRUE;
		}
	// else check if logged in user is qpp advisor or manager && the state matches with practice state	
	}elseif(in_array('QPP Advisor', $user->roles) OR in_array('QPP Manager', $user->roles)){
		$practice_state = qpp_check_practice_state($pid);
		$participating_states = qpp_check_participating_state($user->uid);
		if(in_array($practice_state, $participating_states)){
			return TRUE;
		}
		$grant_sdo = qpp_check_grant_sdo($pid);
		$commercial_sdo = qpp_check_commercial_sdo($pid);
		$sdo_assigned = qpp_check_sdo_assigned($user->uid);
		if(in_array($grant_sdo, $sdo_assigned)){
			return TRUE;
		}
		if(in_array($commercial_sdo, $sdo_assigned)){
			return TRUE;
		}
	// else check if logged in user is Altarum Advisor, Manager or Administrator
	}elseif(in_array('Altarum Advisor', $user->roles) OR in_array('Altarum Manager', $user->roles) OR in_array('Administrator', $user->roles)){
		return TRUE;
	}else{
		return FALSE;
	}
}

// QPP Resource Node Load (for Education pages)
function qpp_resource_load($nid){
	$resource = '';
	if($nid){
		$node = node_load($nid);
		$resource .= (isset($node->title) ? '<h2>'.$node->title.'</h2>' : '');	
		$resource .= (isset($node->body['und'][0]['value']) ? qpp_load_node_field_by_type('node',$node,'body') : '');	
		$resource .= (isset($node->field_resource_type['und'][0]['tid']) ? '<div class="field-items">'.strip_tags(qpp_load_node_field_by_type('node',$node,'field_resource_type')).'</div>' : '');	
		$resource .= (isset($node->field_resource['und'][0]['fid']) ? qpp_load_node_field_by_type('node',$node,'field_resource') : '');	
		$resource .= (isset($node->field_resource_link['und'][0]['url']) ? qpp_load_node_field_by_type('node',$node,'field_resource_link') : '');	
		$resource .= (isset($node->field_resource_video['und'][0]['fid']) ? qpp_load_node_field_by_type('node',$node,'field_resource_video') : '');	
	}
	return $resource;
}

// qpp load node fields for each content type
function qpp_load_node_field_by_type($entity_type, $entity, $field_name){
	$field = '';
 	$type = ($entity_type == 'node') ? $entity->type : 'user';
	$items = field_get_items($entity_type, $entity, $field_name);
	$info = field_info_instance($entity_type, $field_name, $type);
	if(!empty($items)){
		foreach($items as $item) {
			$value = field_view_value($entity_type, $entity, $field_name, $item);
			if(!empty($value)) {
				$field .= '<div class="field-items">'.drupal_render($value).'</div>';
			}
		}
	}	
	return $field;
}

// qpp recommended actions and resources
function qpp_recommended_actions_table($nid){
	$content = '';
	if($nid){
		$node = node_load($nid);
		$content .= $node->field_recommended_action['und'][0]['value'];
		if(isset($node->field_resources['und'])){
			$content .= '<ul>';
			foreach($node->field_resources['und'] as $resource){
				$content .= '<li>'.qpp_set_path(node_load($resource['target_id'])->nid).'</li>';
			}
			$content .= '</ul>';
		}				
	}
	return $content;
}

// set term name
function qpp_set_term_name($tid){
	$term = '';
	$term_obj = taxonomy_term_load($tid);
	if(isset($term_obj) && !empty($term_obj)){
		$term = $term_obj->name;
	}
	return $term;
}

/* set path for node titles */
function qpp_set_path($nid){
	global $base_url;
	$node = node_load($nid);
	$path = drupal_get_path_alias("node/$nid");
	$title_raw = $node->title;
	$title = '<a href="'.$base_url.'/'.$path.'" title="'.$title_raw.'">'.$title_raw.'</a>';
	return $title;
}
?>