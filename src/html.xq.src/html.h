/*
 * Copyright 2006-2008 The FLWOR Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ZORBA_HTMLMODULE_HTML_H
#define ZORBA_HTMLMODULE_HTML_H

#include <map>

#include <zorba/zorba.h>
#include <zorba/function.h>
#include <zorba/external_module.h>

namespace zorba
{
  namespace htmlmodule
  {

//*****************************************************************************
//*****************************************************************************
class HtmlModule : public ExternalModule
{
protected:
  class ltstr
  {
  public:
    bool operator()(const String& s1, const String& s2) const
    {
      return s1.compare(s2) < 0;
    }
  };

  typedef std::map<String, ExternalFunction*, ltstr> FuncMap_t;

protected:
  ItemFactory      * theFactory;
  XmlDataManager_t   theDataMgr;
  FuncMap_t          theFunctions;

public:
  HtmlModule();

  virtual ~HtmlModule();

  virtual String
  getURI() const { return "http://www.zorba-xquery.com/modules/converters/html"; }

  virtual ExternalFunction*
  getExternalFunction(const String& aLocalname);

  virtual void
  destroy();

  ItemFactory* getItemFactory() const { return theFactory; }

  XmlDataManager* getDataMgr() const { return theDataMgr.get(); }
};


//*****************************************************************************
//*****************************************************************************
class HtmlFunction : public ContextualExternalFunction
{
protected:
  const HtmlModule* theModule;

public:
  HtmlFunction(const HtmlModule* aModule) : theModule(aModule) {};

  ~HtmlFunction() {};

  virtual String
  getURI() const { return theModule->getURI(); }
};


//*****************************************************************************
//*****************************************************************************
class ParseFunction : public HtmlFunction
{
public:
  ParseFunction(const HtmlModule* aModule);

  virtual String
  getLocalName() const { return "parse-internal"; }

  virtual ItemSequence_t
  evaluate(const ExternalFunction::Arguments_t& args,
           const StaticContext* aSctxCtx,
           const DynamicContext* aDynCtx) const;
};




} /* namespace htmlmodule */ 
} /* namespace zorba */

#endif /* ZORBA_HTMLMODULE_HTML_H */
