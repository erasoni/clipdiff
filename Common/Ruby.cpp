//Copyright (C) 2017 Ambiesoft All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//1. Redistributions of source code must retain the above copyright
//notice, this list of conditions and the following disclaimer.
//2. Redistributions in binary form must reproduce the above copyright
//notice, this list of conditions and the following disclaimer in the
//documentation and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//SUCH DAMAGE.

#include "stdafx.h"
#include "Ruby.h"
#include "../../lsMisc/cppclr/clrHelper.h"
#include "../../lsMisc/cppclr/clrString.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Windows::Forms;

using namespace std;


namespace Ambiesoft {

	void Ruby::init()
	{
		if (initialized_)
			return;
		initialized_ = true;
		
		//wstring thisdir = stdGetParentDirectory(stdGetModuleFileName());
		//wstring rubyexe = stdCombinePath(thisdir, L"docdiff\\ruby1.8\\bin\\ruby.exe");
		//wstring rubylibdir = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3");
		//wstring docdiffrb = stdCombinePath(thisdir, L"docdiff\\docdiff-0.3.3\\docdiff.rb");
		//wstring t = stdGetEnvironmentVariable(L"RUBYLIB");

		//if (t.empty())
		//	t = rubylibdir.c_str();
		//else
		//	t = rubylibdir + L";" + t;
		//SetEnvironmentVariable(L"RUBYLIB", t.c_str());


		rubyexe_ = L"docdiff\\ruby1.8\\bin\\ruby.exe";// gcnew String(rubyexe.c_str());
		docdiffrb_ = L"docdiff\\docdiff-0.3.3\\docdiff.rb";//gcnew String(docdiffrb.c_str());
		docdifflibdir_ = L"docdiff\\docdiff-0.3.3";
	}

	void Ruby::RunRuby(System::String^ commandline,
		System::String^% out, System::String^% err)
	{
		String^ dir = Path::GetDirectoryName(Application::ExecutablePath);
		TemporalCurrentDir tmpdir(dir);

		OpenCommnadGetResult(Ruby::RubyExe,
			L"-v",
			Encoding::UTF8,
			out,
			err);
	}	
	void Ruby::RunDocDiff(System::String^ commandline,
		System::String^% out, System::String^% err)
	{
		String^ dir = Path::GetDirectoryName(Application::ExecutablePath);
		TemporalCurrentDir tmpdir(dir);

		String^ clrCommandLine = String::Format(L"{0} {1} {2}",
			L"-I" + doubleQuote(Ruby::DocDiffLibDir),
			doubleQuote(Ruby::DocDiffrb),
			commandline);

		OpenCommnadGetResult(Ruby::RubyExe,
			clrCommandLine,
			Encoding::UTF8,
			out,
			err);
	}
}