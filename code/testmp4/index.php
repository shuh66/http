<?php  
/* 接收请求的API */ 

header("Access-Control-Allow-Origin: *");
//$val="";  
if($_POST){  
 //echo 'woqushanghaidedota2';

    $recContent=$_POST['filedata'];
   //echo $recContent;
    //echo $ad;
    $a=substr($recContent,0,strpos($recContent, '/'));
    $data65=base64_decode($a);
    @$data = fopen("log".date('YmdHis',time())."_".$data65,'a+');
    fwrite($data,$recContent);//写入文本中  
fclose($data);     
}else{  
 echo 'error';  
} ?> 

