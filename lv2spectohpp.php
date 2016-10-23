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

function CamelCase(string $str)
	{
//TODO: Use preg_split instead...
	$x=explode(' ',$str);
	foreach($x as &$namepart)
		{$namepart=ucfirst($namepart);}
	return implode('',$x);
	}

function guardname(string $scope,string $filename)
	{
//TODO: Use preg_split instead...
	$x=[$scope];
	$x=array_merge($x,explode('.',$filename));
	foreach($x as &$namepart)
		{$namepart=strtoupper($namepart);}
	return implode('_',$x);
	}

function cxxconstant(string $name)
	{
//TODO: Use preg_split instead...
	$x=explode(' ',$name);
	foreach($x as &$namepart)
		{$namepart=strtoupper($namepart);}
	return implode('_',$x);
	}

function typeGet($port)
	{
	$ret='';
	if($port->{'direction'}=='in')
		{$ret.='const ';}
	$typemap=array('midi'=>'LV2_Atom_Sequence*'
		,'audio'=>'float*'
		,'control'=>'float');
	$ret.=$typemap[$port->{'type'}];
	return $ret;
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
$content=json_decode(file_get_contents($argv[1]));
$plugindata=$content->{'specification'};
$name=$plugindata->{'name'};
$namespace=CamelCase($name);
$guard=guardname($namespace,$content->{'targets'}[0]->{'name'});
$now=new DateTime();
?>
// <?=$name?> descriptor include file
//
// This file has been generated from <?=$argv[1]?> <?=$now->format('Y-m-d H:i') ?> by
// <?=$argv[0]?>. Changes to this file may be overwritten
// during compilation of the project.

#ifndef <?=$guard?>

#define <?=$guard?>

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>

namespace <?=$namespace?>

	{
	struct PluginDescriptor
		{
<?php foreach($plugindata as $field => $value)
	{
	if(!is_array($value) && !is_object($value))
		{
		$constant=cxxconstant($field);?>
		static constexpr const char* <?=strtolower($constant)?>() noexcept
			{return "<?=$value?>";}

<?php	}
	} ?>
		static constexpr unsigned int portCount()
			{return <?=count($plugindata->{'ports'}) ?>;}

<?php if(isset($plugindata->{'ui'})) {?>
		static constexpr const char* uiUri() noexcept
			{return "<?=$plugindata->{'ui'}->{'uri'} ?>";}
<?php }?>

		struct Ports
			{
<?php foreach($plugindata->{'ports'} as $index=>$port) {?>
			static constexpr unsigned int <?=cxxconstant($port->{'name'})?>=<?=$index ?>;
<?php }?>
			static constexpr const char* PORTNAMES[]={<?php foreach($plugindata->{'ports'} as $index=>$port)
	{
	echo '"'.$port->{'name'}.'",';
	}?>nullptr};
			};

		template<unsigned int port_id>
		struct Port
			{
			typedef void type;
			};
		};
<?php foreach($plugindata->{'ports'} as $index=>$port) {?>

	template<>
	struct PluginDescriptor::Port<PluginDescriptor::Ports::<?=cxxconstant($port->{'name'})?>>
		{
		typedef <?=typeGet($port)?> type;
		static constexpr unsigned int id() noexcept
			{return <?=$index?>;}

		static constexpr const char* name() noexcept
			{return "<?=$port->{'name'}?>";}
<?php if(isset($port->{'minimum'})){ ?>
		static constexpr type minimum() noexcept
			{return static_cast<type>(<?=$port->{'minimum'}?>);}
<?php } ?>
<?php if(isset($port->{'maximum'})){ ?>
		static constexpr type maximum() noexcept
			{return static_cast<type>(<?=$port->{'maximum'}?>);}
<?php } ?>
<?php if(isset($port->{'default'})){ ?>
		static constexpr type valueDefault() noexcept
			{return static_cast<type>(<?=$port->{'default'}?>);}
<?php } ?>
		};
<?php }?>
	}
#endif
<?php 
$ob_file=fopen($argv[2].'/'.$content->{'targets'}[0]->{'name'},'w','w');
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