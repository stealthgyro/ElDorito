#pragma once

#include <Windows.h>

#include <vector>
#include "Utils/Singleton.h"


typedef std::string(*CommandUpdateFunc)(const std::vector<std::string>& Arguments);


namespace
{
	unsigned long stou(std::string const & str, size_t * idx = 0, int base = 10);
	PCHAR* CommandLineToArgvA(PCHAR CmdLine, int* _argc);
}

namespace Modules
{
	enum CommandType
	{
		eCommandTypeCommand,
		eCommandTypeVariableInt,
		eCommandTypeVariableFloat,
		eCommandTypeVariableString
	};
	struct Command
	{
		std::string Name; // modulename is added to this too, makes looking it up easier
		std::string ModuleName;
		std::string ShortName; // because some people can't be bothered to type in module names
		std::string Description;

		CommandType Type;

		CommandUpdateFunc UpdateEvent;

		unsigned long ValueInt;
		float ValueFloat;
		std::string ValueString;

		unsigned long DefaultValueInt;
		float DefaultValueFloat;
		std::string DefaultValueString;

		unsigned long ValueIntMin;
		unsigned long ValueIntMax;
		float ValueFloatMin;
		float ValueFloatMax;

		// CommandArgs is only used for help text, commands will have to parse the args themselves

		std::vector<std::string> CommandArgs; // arg names can't contain a space, since space/EOL is used to find where the command name ends and the command description begins
		// this is for the help function, so you can specify an arg here like "parameter_1 This parameter controls the first parameter"
		// in the help text this will be printed like "Usage: Game.Command <parameter_1>\r\nparameter_1: This parameter controls the first parameter."
		// also don't end descriptions with a period since it'll be added in later
		// modifiers might be added to the name later, so you can do things like "parameter_1:o" to signify the parameter is optional
		Command();
		std::string GenerateHelpText();
	};

	class CommandMap : public Utils::Singleton<CommandMap>
	{
	public:
		Command* AddCommand(Command command);
		Command* FindCommand(const std::string& name);
		std::string ExecuteCommand(std::vector<std::string> command);
		std::string ExecuteCommand(std::string command);

		bool GetVariableInt(const std::string& name, unsigned long& value);
		bool GetVariableFloat(const std::string& name, float& value);
		bool GetVariableString(const std::string& name, std::string& value);

		std::string GenerateHelpText();

		std::vector<Command> Commands;
	};
}