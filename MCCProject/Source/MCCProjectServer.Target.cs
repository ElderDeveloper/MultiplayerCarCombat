// Copyright 2023 Kevuru LLC All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MCCProjectServerTarget : TargetRules
{
	public MCCProjectServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MCCProject");
	}
}
