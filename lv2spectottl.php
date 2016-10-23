#!/usr/bin/env php
<?php
function exception_error_handler($errno, $errstr, $errfile, $errline ) {
    throw new ErrorException($errstr, $errno, 0, $errfile, $errline);
}
set_error_handler("exception_error_handler");
try
{
$output_buffer='';
function ob_file_callback($buffer)
	{
	global $output_buffer;
	$output_buffer.=$buffer;
	}
ob_start('ob_file_callback');

function symbolFromName(string $name)
	{
//TODO: Use preg_split instead...
	$x=explode(' ',$name);
	return implode('_',$x);
	}

function typeGet($port)
	{
	$ret='';
	if($port->{'direction'}=='in')
		{$ret.='a lv2:InputPort,';}
	else
		{$ret.='a lv2:OutputPort,';}
	$typemap=array('midi'=>'atom:AtomPort'
		,'audio'=>'lv2:AudioPort'
		,'control'=>'lv2:ControlPort');
	$ret.=$typemap[$port->{'type'}];
	return $ret;
	}

function uitype($type)
	{
	$typemap=array(
		 'Cocoa'=>'CocoaUI'
		,'Gtk2'=>'GtkUI'
		,'Gtk'=>'GtkUI'
		,'Gtk3'=>'Gtk3UI'
		,'MacOSX Native'=>'CocoaUI'
		,'Qt4'=>'Qt4UI'
		,'Qt5'=>'Qt5UI'
		,'Windows Native'=>'WindowsUI'
		,'X11'=>'X11UI');
	return $typemap[$type];
	}


if($argc<2)
	{
	error_log('No input file is specified');
	exit(-1);
	}

if($argc<3)
	{
	error_log('No target directory is specified');
	exit(-1);
	}
$plugindata=json_decode(file_get_contents($argv[1]))->{'specification'};
$now=new DateTime();
?>
# <?=$plugindata->{'name'}?> manifest file
#
# This file has been generated from <?=$argv[1]?> <?=$now->format('Y-m-d H:i') ?> by
# <?=$argv[0]?>. Changes to this file may be overwritten
# during compilation of the project.

@prefix atom: <http://lv2plug.in/ns/ext/atom#> .
@prefix doap: <http://usefulinc.com/ns/doap#> .
@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .
@prefix midi: <http://lv2plug.in/ns/ext/midi#> .
@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .
@prefix urid: <http://lv2plug.in/ns/ext/urid#> .
@prefix ui: <http://lv2plug.in/ns/extensions/ui#> .
@prefix foaf: <http://xmlns.com/foaf/0.1/> .

<?php if(isset($plugindata->{'ui'})) {?>
<<?=$plugindata->{'ui'}->{'uri'}?>>
	a ui:<?=uitype($plugindata->{'ui'}->{'type'})?>;
	ui:binary <<?=$plugindata->{'ui'}->{'binary'}?>>.
<?php }?>

<<?=$plugindata->{'uri'}?>>
	a lv2:Plugin;
	a lv2:<?=$plugindata->{'type'}?>;
	lv2:binary <<?=$plugindata->{'binary'}?>>;
	doap:name "<?=$plugindata->{'name'}?>";
	doap:maintainer [ foaf:name "<?=$plugindata->{'maintainer'}?>" ; ] ;
	doap:license <<?=$plugindata->{'license'}?>>
<?php if(isset($plugindata->{'ui'})) {?>
	ui:ui <<?=$plugindata->{'ui'}->{'uri'}?>>;
<?php }?>

lv2:port
<?php foreach($plugindata->{'ports'} as $index=>$port) {?>
	[
	<?=typeGet($port)?>;
	lv2:index <?=$index?>;
	lv2:symbol "<?=symbolFromName($port->{'name'})?>";
	lv2:name "<?=$port->{'name'}?>";
<?php if($port->{'type'}=='control') {?>
	lv2:minimum <?=$port->{'minimum'}?>;
	lv2:maximum <?=$port->{'maximum'}?>;
	lv2:default <?=$port->{'default'}?>;
<?php } else if($port->{'type'}=='midi') {?>
	atom:bufferType atom:Sequence ;
	atom:supports <http://lv2plug.in/ns/ext/midi#MidiEvent>,<http://lv2plug.in/ns/ext/time#Position> ;
<?php } ?>
	]<?=$port==end($plugindata->{'ports'})?'.':','?>

<?php }?>
<?php 
$ob_file=fopen($argv[2].'/manifest.ttl','w');
ob_flush();
fwrite($ob_file,$output_buffer);
}
catch(Exception $e)
{
error_log($e->getMessage());
exit(-1);
}
exit(0);
?>