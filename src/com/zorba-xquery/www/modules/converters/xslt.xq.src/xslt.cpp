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

#include <zorba/empty_sequence.h>
#include <zorba/singleton_item_sequence.h>
#include <zorba/item.h>

#include "xslt.h"

/*#include "api/serialization/serializer.h"
#include "compiler/api/compilercb.h"
#include "context/static_context.h"
#include "runtime/api/plan_iterator_wrapper.h"
#include "store/api/store.h"
*/
#include <stdio.h>
#include <string.h>
#include <zorba/serializer.h>

#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>


namespace zorba 
{
  namespace xsltmodule
  {

/*
bool
ZorbaXsltTransformIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t source;
  store::Item_t stylesheet;
  ////store::ItemFactory* factory = GENV_ITEMFACTORY;
  std::stringstream lResultStream;
    
  PlanIteratorState *state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if ( theChildren.size() == 2  )
  {

    {
      zorba::serializer lSerializer(planState.theCompilerCB->theErrorManager);
      store::Iterator_t lSourceWrapper = new PlanIteratorWrapper(theChildren[0], planState);
      store::Iterator_t lStylesheetWrapper = new PlanIteratorWrapper(theChildren[1], planState);

      // and now serialize
      lSerializer.serialize(lSourceWrapper, lResultStream);
      zstring source = lResultStream.str();            
      
      lResultStream.str("");
      
      lSerializer.serialize(lStylesheetWrapper, lResultStream);
      zstring stylesheet = lResultStream.str();
      
      
      // start using libxslt       
      xsltStylesheetPtr cur = NULL;
      xmlDocPtr stylesheetDoc, instDoc, res;
      const char *params[0 + 1];
      int nbparams = 0;
      params[nbparams] = NULL;
  
      xmlChar* ssStr = BAD_CAST stylesheet.c_str(); //xmlCharStrdup(stylesheet.c_str());
      stylesheetDoc = xmlParseDoc( ssStr );
      cur = xsltParseStylesheetDoc(stylesheetDoc);
      
      xmlChar* srcStr = BAD_CAST source.c_str(); //xmlCharStrdup(source.c_str());
      instDoc = xmlParseDoc( srcStr );
      res = xsltApplyStylesheet(cur, instDoc, params);
      //int transforResult = xsltSaveResultToFile(stdout, res, cur);
      xmlChar* xcRes;
      int len;
      int transforResult = xsltSaveResultToString(&xcRes, &len, res, cur);

      xsltFreeStylesheet(cur);
      //avoid doing xmlFreeDoc(stylesheetDoc);
      xmlFreeDoc(res);
      xmlFreeDoc(instDoc);
      
      xsltCleanupGlobals();
      xmlCleanupParser();

      zstring resStr( (char *) xcRes);   
      xmlFree(xcRes);
      
      if ( transforResult != 0 )
      {
        throw XQUERY_EXCEPTION(
          FODC0006, ERROR_PARAMS( "XSLT Error" ), ERROR_LOC( loc )
        );
      }
      
      ////factory->createString(result, resStr);
      
      std::auto_ptr<std::istringstream> iss;
      std::istream *is;
      
      iss.reset (new std::istringstream(resStr.c_str()));
      is = iss.get();
      
      zstring docUri;
      zstring baseUri = theSctx->get_base_uri();
      
      try 
      {
        store::LoadProperties loadProps;
        loadProps.setStoreDocument(false);
        store::Store& lStore = GENV.getStore();
        result = lStore.loadDocument(baseUri, docUri, *is, loadProps);
      } 
      catch (ZorbaException const& e) 
      {
        throw XQUERY_EXCEPTION(
          FODC0006, ERROR_PARAMS( e.what() ), ERROR_LOC( loc )
        );
      }      
    }
    
    STACK_PUSH(true, state);
  }

  STACK_END (state);
}
*/
//to do cezar: Morph the previous content into the following by using the public API
/*****************************************************************************
 * TransformFunction implementation
 ***************************************************************************/

ItemSequence_t
TransformFunction::evaluate(
  const StatelessExternalFunction::Arguments_t& aArgs,
  const StaticContext*                          aSctxCtx,
  const DynamicContext*                         aDynCtx) const
{
  //std::auto_ptr<std::istringstream> iss;
  //std::istream *is;
  Item lSourceItem, lStylesheetItem;

  if (aArgs.size() != 2)
  {
    // todo error out 
    return NULL;
  }

  Iterator_t lArg0Iter = aArgs[0]->getIterator();
  lArg0Iter->open();
  lArg0Iter->next(lSourceItem);
  lArg0Iter->close();

  Iterator_t lArg1Iter = aArgs[1]->getIterator();
  lArg1Iter->open();
  lArg1Iter->next(lStylesheetItem);
  lArg1Iter->close();

  Zorba_SerializerOptions_t lOptions;
  Serializer_t lSerializer = Serializer::createSerializer(lOptions);
  
  std::stringstream lResultStream;
  SingletonItemSequence lSrcSequence(lSourceItem);
  lSerializer->serialize(&lSrcSequence, lResultStream);
  std::string lSource = lResultStream.str();            
    
  lResultStream.str("");
    
  SingletonItemSequence lStyleSequence(lStylesheetItem);
  lSerializer->serialize(&lStyleSequence, lResultStream);
  std::string lStylesheet = lResultStream.str();
  

  // start using libxslt       
  xsltStylesheetPtr cur = NULL;
  xmlDocPtr stylesheetDoc, instDoc, res;
  const char *params[0 + 1];
  int nbparams = 0;
  params[nbparams] = NULL;

  xmlChar* ssStr = BAD_CAST lStylesheet.c_str(); //xmlCharStrdup(stylesheet.c_str());
  stylesheetDoc = xmlParseDoc( ssStr );
  cur = xsltParseStylesheetDoc(stylesheetDoc);
  
  xmlChar* srcStr = BAD_CAST lSource.c_str(); //xmlCharStrdup(source.c_str());
  instDoc = xmlParseDoc( srcStr );
  res = xsltApplyStylesheet(cur, instDoc, params);
  //int transforResult = xsltSaveResultToFile(stdout, res, cur);
  xmlChar* xcRes;
  int len;
  int transforResult = xsltSaveResultToString(&xcRes, &len, res, cur);

  xsltFreeStylesheet(cur);
  //avoid doing xmlFreeDoc(stylesheetDoc);
  xmlFreeDoc(res);
  xmlFreeDoc(instDoc);
  
  xsltCleanupGlobals();
  xmlCleanupParser();

  std::string resStr( (char *) xcRes);   
  xmlFree(xcRes);
  
  if ( transforResult != 0 )
  {
    /* todo   throw XQUERY_EXCEPTION(
      FODC0006, ERROR_PARAMS( "XSLT Error" ), ERROR_LOC( loc )
    );*/
    return NULL;
  }
  
  std::istringstream iss( resStr.c_str() ); 
  
  XmlDataManager* lDM = Zorba::getInstance(0)->getXmlDataManager();
  try
  {
    return ItemSequence_t(new SingletonItemSequence(lDM->parseXML(iss)));   
  } 
  catch (ZorbaException&)
  {
    return NULL;
  }
}



/*****************************************************************************
 * XsltModule implementation
 ***************************************************************************/

ItemFactory* XsltModule::theFactory = 0;

XsltModule::~XsltModule()
{
  for ( FuncMap_t::const_iterator lIter = theFunctions.begin();
        lIter != theFunctions.end();
        ++lIter)
       {
         delete lIter->second;
       }
       theFunctions.clear();
}

StatelessExternalFunction*
XsltModule::getExternalFunction(const String& aLocalname)
{
  StatelessExternalFunction*& lFunc = theFunctions[aLocalname];
  if (!lFunc)
  {
    if (1 == 0)
    { }
    else if (aLocalname == "transform")
    {
      lFunc = new TransformFunction(this);
    }
  }
  return lFunc;
}

void
XsltModule::destroy()
{
  if (!dynamic_cast<XsltModule*>(this))
  {
    return;
  }
  delete this;
}


  } /* namespace xsltmodule */
} /* namespace zorba */

#ifdef WIN32
#  define DLL_EXPORT __declspec(dllexport)
#else
#  define DLL_EXPORT __attribute__ ((visibility("default")))
#endif

extern "C" DLL_EXPORT zorba::ExternalModule* createModule()
{
  return new zorba::xsltmodule::XsltModule();
}
