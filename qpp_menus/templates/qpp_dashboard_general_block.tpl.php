<?php
 global $user;
$aid = $user->uid;
$date = $user->login;
$access = format_date($date, 'custom','Y-m-d/H:i:s');  
 // Checking server
$mipscastlink ='';
global $base_url;
if($base_url == 'https://www.qppresourcecenter.com'){
$mipscastlink = 'https://mipscast.org/altarum/qppconnector?uid=' . $aid .'&access=' . $date;
}elseif($base_url == 'https://stage.qppresourcecenter.com'){
$mipscastlink = 'https://glptntraining.altarum.org/altarum/qppconnector?uid=' . $aid .'&access=' . $date;
}elseif($base_url == 'https://dev.qppresourcecenter.com'){
$mipscastlink ='https://glptnqa.altarum.org/altarum/qppconnector?uid=' . $aid .'&access=' . $date;	
}else{
$mipscastlink ='https://glptnqa.altarum.org/altarum/qppconnector?uid=' . $aid .'&access=' . $date;
}

  if(in_array('Administrator', $user->roles) OR in_array('Altarum Manager', $user->roles) OR in_array('Altarum Advisor', $user->roles) OR in_array('QPP Manager', $user->roles) OR in_array('QPP Advisor', $user->roles)){ 
print  '<ul class="dashboard-menu nav">
              <li class="leaf"><a href="/dashboard">Dashboard</a></li>
			   <li class="leaf"><a href="/user">My Account</a></li>
			   <li class="leaf"><a target="_blank" href="' . $mipscastlink . '">View MIPS<em>cast&#8482;</em></a></li>
            </ul>';
	
	
}
?>