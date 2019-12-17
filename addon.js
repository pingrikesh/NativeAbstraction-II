var addon = require('bindings')('addon');
const fs = require('fs');
const util = require('util');
const file = 'input.txt';
const readFile = util.promisify(fs.readFile);

function jsCompare(arr)
{
	
	let newArr=[];
	newArr=arr.sort((a,b)=>a.length-b.length);
	newArr=arr.slice(arr.length - 10);
	newArr=newArr.reverse();
	//console.log(newArr);
	return newArr;
}

async function getStuff() {
  return await readFile(file,'utf8');
}

getStuff().
then(data => data.split(/[ .,;:\/ -]/)).
then(data=>
	{
	console.log("-----------------This is according to C++-----------------------");
	console.log(addon.getSetGo(data));
	console.log("//********************************************************************************//");
	console.log("-----------------This is according to JavaScript-----------------------");
	console.log(jsCompare(data));

	if(JSON.stringify(addon.getSetGo(data))===JSON.stringify(jsCompare(data)))
	{console.log("The Results are same. Hence, Proved. Thank you!")}
	}
).
catch(error => {throw error});







 




