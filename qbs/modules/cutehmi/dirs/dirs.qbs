import qbs
import qbs.TextFile

import "private.js" as Private

/**
  Project directories. This module acts as central configuration point and lookup facility for project directories. It can also
  generate 'cutehmi.dirs.hpp' artifact for a product, which contains macros describing directory locations.
  */
Module {
	setupRunEnvironment: {
		Private.setupEnvironment()
	}

	setupBuildEnvironment: {
		Private.setupEnvironment()
	}

	PropertyOptions {
		name: "artifacts"
		description: "Whether to generate any artifacts."
	}
	property bool artifacts: false

	PropertyOptions {
		name: "dirsHppArtifact"
		description: "Actual filename of artifact tagged as 'cutehmi.dirs.hpp'. If set to undefined artifact won't be generated."
	}
	property path dirsHppArtifact: artifacts ? "cutehmi.dirs.hpp" : undefined

	PropertyOptions {
		name: "installDir"
		description: "Project instalation directory composed of 'qbs' properties describing instalation path."
	}
	readonly property string installDir: product.qbs.installPrefix ? product.qbs.installRoot + product.qbs.installPrefix : product.qbs.installRoot // Note: qbs.installPrefix starts with "/".

	readonly property string examplesInstallSubdir: "examples" 	///< @deprecated Examples are going to be entirely replaced by appropriate example extensions.

	PropertyOptions {
		name: "extensionInstallSubdir"
		description: "Target intallation subdirectory for an extension."
	}
	// <qbs-cutehmi.dirs-1.workaround target="Qt" cause="design">
	// Android expects QML files to be installed in 'qml' directory, so we're changing installation path of extension files.
	readonly property string extensionInstallSubdir: qbs.targetOS.contains("android") ? "qml" : "cutehmi"
	// </qbs-cutehmi.dirs-1.workaround>

	PropertyOptions {
		name: "extensionsSourceDir"
		description: "Directory where source code of extensions reside."
	}
	readonly property string extensionsSourceDir: project.sourceDirectory + "/extensions"

	PropertyOptions {
		name: "externalDeployDir"
		description: "Deployment directory of external libraries."
	}
	readonly property string externalDeployDir: project.sourceDirectory + "/external/deploy"

	PropertyOptions {
		name: "externalLibDir"
		description: "Directory containing external libraries binaries."
	}
	readonly property string externalLibDir: externalDeployDir + "/lib"

	PropertyOptions {
		name: "externalIncludeDir"
		description: "Directory containing external libraries includes."
	}
	readonly property string externalIncludeDir: externalDeployDir + "/include"

	PropertyOptions {
		name: "puppetSourceSubdir"
		description: "subdirectory containing QML puppet files to be used with Qt Designer."
	}
	readonly property string puppetSourceSubdir: "puppet"

	PropertyOptions {
		name: "puppetInstallSubdir"
		description: "Installation subdirectory of puppet extensions that are used by Qt Designer."
	}
	readonly property string puppetInstallSubdir: "cutehmi_puppets"

	PropertyOptions {
		name: "testInstallSubdir"
		description: "Target intallation subdirectory for a test."
	}
	readonly property string testInstallSubdir: "cutehmi"

	PropertyOptions {
		name: "toolInstallSubdir"
		description: "Target intallation subdirectory for a tool."
	}
	readonly property string toolInstallSubdir: "cutehmi"

	Rule {
		condition: product.cutehmi.dirs.dirsHppArtifact !== undefined
		multiplex: true

		prepare: {
			var hppCmd = new JavaScriptCommand();
			hppCmd.description = "generating " + output.filePath
			hppCmd.highlight = "codegen";
			hppCmd.sourceCode = function() {
				var f = new TextFile(output.filePath, TextFile.WriteOnly);
				try {
					var prefix = "CUTEHMI_DIRS"

					f.writeLine("#ifndef " + prefix + "_HPP")
					f.writeLine("#define " + prefix + "_HPP")

					f.writeLine("")
					f.writeLine("// This file has been autogenerated by 'cutehmi.dirs' Qbs module.")
					f.writeLine("")

					f.writeLine("#define " + prefix + "_TOOL_INSTALL_SUBDIR \"" + product.cutehmi.dirs.toolInstallSubdir + "\"")
					f.writeLine("#define " + prefix + "_TEST_INSTALL_SUBDIR \"" + product.cutehmi.dirs.testInstallSubdir + "\"")
					f.writeLine("#define " + prefix + "_EXTENSION_INSTALL_SUBDIR \"" + product.cutehmi.dirs.extensionInstallSubdir + "\"")
					f.writeLine("#define " + prefix + "_PUPPET_INSTALL_SUBDIR \"" + product.cutehmi.dirs.puppetInstallSubdir + "\"")
					f.writeLine("")
					f.writeLine("#endif")
				} finally {
					f.close()
				}
			}

			return [hppCmd]
		}

		Artifact {
			filePath: product.cutehmi.dirs.dirsHppArtifact
			fileTags: ["cutehmi.dirs.hpp", "hpp"]
		}
	}
}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
