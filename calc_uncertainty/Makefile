# -*- mode: makefile -*-
#
# Makefile containing platform dependencies different projects.
MAKEFLAGS = --no-print-directory -r -s -j2


ARCH_LOC_1 := $(wildcard $(shell root-config --prefix)/etc/Makefile.arch)
ARCH_LOC_2 := $(wildcard $(shell root-config --prefix)/etc/root/Makefile.arch)
ARCH_LOC_3 := $(wildcard $(shell root-config --prefix)/share/doc/root/test/Makefile.arch)
ifneq ($(strip $(ARCH_LOC_1)),)
  $(info Using $(ARCH_LOC_1))
  include $(ARCH_LOC_1)
else
  ifneq ($(strip $(ARCH_LOC_2)),)
    $(info Using $(ARCH_LOC_2))
    include $(ARCH_LOC_2)
  else
    ifneq ($(strip $(ARCH_LOC_3)),)
      $(info Using $(ARCH_LOC_3))
      include $(ARCH_LOC_3)
    else
      $(error Could not find Makefile.arch!)
    endif
  endif
endif


CXXFLAGS += -Wall -Wno-overloaded-virtual -Wno-unused -std=c++11

INCLUDES += -I./inc -I/users/yanght/include 

VPATH	= ./src ./inc ./ws

OBJS_runAsymptoticsCLs	= obj/runAsymptoticsCLs.o obj/statistics.o obj/statisticsDict.o obj/CommonFunc.o obj/CommonFuncDict.o obj/Background.o obj/BackgroundDict.o obj/HggTwoSidedCBPdf.o obj/HggTwoSidedCBPdfDict.o obj/FlexibleInterpVarMkII.o obj/FlexibleInterpVarMkIIDict.o
OBJS_toy	= obj/toy.o obj/statistics.o obj/statisticsDict.o obj/CommonFunc.o obj/CommonFuncDict.o obj/Background.o obj/BackgroundDict.o obj/HggTwoSidedCBPdf.o obj/HggTwoSidedCBPdfDict.o obj/FlexibleInterpVarMkII.o obj/FlexibleInterpVarMkIIDict.o obj/HggTruthLineShapePdf.o obj/HggTruthLineShapePdfDict.o
OBJS_rsinput	= obj/rsinput.o obj/CommonFunc.o obj/CommonFuncDict.o 
OBJS_toyHighMassgg	= obj/toyHighMassgg.o obj/statistics.o obj/statisticsDict.o obj/CommonFunc.o obj/CommonFuncDict.o obj/Background.o obj/BackgroundDict.o obj/HggTwoSidedCBPdf.o obj/HggTwoSidedCBPdfDict.o obj/FlexibleInterpVarMkII.o obj/FlexibleInterpVarMkIIDict.o obj/HggGravitonLineShapePdf.o obj/HggGravitonLineShapePdfDict.o obj/HggScalarLineShapePdf.o obj/HggScalarLineShapePdfDict.o obj/toyNtup.o obj/toyNtupDict.o
OBJS_produceMassPointD3PD	= obj/produceMassPointD3PD.o obj/CommonFunc.o obj/CommonFuncDict.o obj/Hgg_tree.o obj/Hgg_treeDict.o 
OBJS_calcCountingSigHighMassgg	= obj/calcCountingSigHighMassgg.o obj/CommonFunc.o obj/CommonFuncDict.o obj/tout.o obj/toutDict.o obj/statistics.o obj/statisticsDict.o obj/gravitonNtup.o obj/gravitonNtupDict.o
OBJS_countHighMassgg	= obj/countHighMassgg.o obj/CommonFunc.o obj/CommonFuncDict.o obj/gravitonNtup.o obj/gravitonNtupDict.o obj/MxAODNtup.o obj/MxAODNtupDict.o
OBJS_testGRL	= obj/testGRL.o obj/MyGRL.o obj/MyGRLDict.o obj/CommonFunc.o obj/CommonFuncDict.o obj/MxAODNtup.o obj/MxAODNtupDict.o
OBJS_parametrizationttH	= obj/parametrizationttH.o obj/CommonFunc.o obj/CommonFuncDict.o obj/statistics.o obj/statisticsDict.o obj/MxAODNtup.o obj/MxAODNtupDict.o obj/test.o obj/testDict.o
OBJS_plotnllscanComb	= obj/plotnllscanComb.o obj/statistics.o obj/statisticsDict.o obj/CommonFunc.o obj/CommonFuncDict.o

OBJS_sensitivityttHCP	= obj/sensitivityttHCP.o obj/CommonFunc.o obj/CommonFuncDict.o obj/truth.o obj/truthDict.o

DEPS_runAsymptoticsCLs	:= $(OBJS_runAsymptoticsCLs:.o=.d) 
DEPS_toy	:= $(OBJS_toy:.o=.d) 
DEPS_toyHighMassgg	:= $(OBJS_toyHighMassgg:.o=.d) 
DEPS_rsinput	:= $(OBJS_rsinput:.o=.d) 
DEPS_produceMassPointD3PD	:= $(OBJS_produceMassPointD3PD:.o=.d) 
DEPS_calcCountingSigHighMassgg	:= $(OBJS_calcCountingSigHighMassgg:.o=.d) 
DEPS_countHighMassgg	:= $(OBJS_countHighMassgg:.o=.d) 
DEPS_testGRL	:= $(OBJS_testGRL:.o=.d) 
DEPS_parametrizationttH	:= $(OBJS_parametrizationttH:.o=.d) 
DEPS_plotnllscanComb	:= $(OBJS_plotnllscanComb:.o=.d)
DEPS_sensitivityttHCP	:= $(OBJS_sensitivityttHCP:.o=.d)

GLIBS	+= -lTMVA -lMLP
GLIBS	+= -lTreePlayer -lProof -lProofPlayer -lutil -lRooFit -lRooFitCore  -lRooStats -lFoam -lMinuit -lHistFactory -lXMLParser -lXMLIO -lCore -lGpad -lMathCore -lPhysics
.PHONY:
	$(OBJS)

-include $(DEPS_runAsymptoticsCLs)
bin/runAsymptoticsCLs: 	$(OBJS_runAsymptoticsCLs)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_toy)
bin/toy: 		$(OBJS_toy)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_testGRL)
bin/testGRL: 		$(OBJS_testGRL)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_toyHighMassgg)
bin/toyHighMassgg: 	$(OBJS_toyHighMassgg)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_rsinput)
bin/rsinput: 		$(OBJS_rsinput)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_produceMassPointD3PD)
bin/produceMassPointD3PD: 		$(OBJS_produceMassPointD3PD)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_calcCountingSigHighMassgg)
bin/calcCountingSigHighMassgg: 		$(OBJS_calcCountingSigHighMassgg)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_countHighMassgg)
bin/countHighMassgg: 	$(OBJS_countHighMassgg)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_parametrizationttH)
bin/parametrizationttH: 	$(OBJS_parametrizationttH)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_plotnllscanComb)
bin/plotnllscanComb: 	$(OBJS_plotnllscanComb)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

-include $(DEPS_sensitivityttHCP)
bin/sensitivityttHCP: 	$(OBJS_sensitivityttHCP)
			@echo "Linking " $@
			echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
			@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@

bin/%	: obj/%.o  obj/CommonFunc.o obj/CommonFuncDict.o obj/statistics.o obj/statisticsDict.o obj/ToolsSignificanceHist.o obj/ToolsSignificanceHistDict.o obj/LEPEntry.o obj/LEPEntryDict.o obj/MxAODNtup.o obj/MxAODNtupDict.o
	@echo "Linking " $@
	echo $(LD) $(LDFLAGS) $^ $(GLIBS) -o $@	
	@$(LD) $(LDFLAGS) $^ $(GLIBS) -o $@ 


obj/%Dict.o:	%.h
		@echo "Compiling $@"
		echo rootcint -f $*Dict.cxx -c $*.h $*LinkDef.h
		rootcint -f $*Dict.cxx -c inc/$*.h inc/$*LinkDef.h
		echo $(CXX) $(INCLUDES) $(CXXFLAGS) -c $*Dict.cxx -o $*Dict.o
		$(CXX) $(INCLUDES) $(CXXFLAGS) -c $*Dict.cxx -o obj/$*Dict.o
		rm -f $*Dict.cxx $*Dict.h 

obj/%Dict.o:	%.hh
		@echo "Compiling $@"
		echo rootcint -f $*Dict.cxx -c $*.hh $*LinkDef.h
		rootcint -f $*Dict.cxx -c inc/$*.hh inc/$*LinkDef.h
		echo $(CXX) $(INCLUDES) $(CXXFLAGS) -c $*Dict.cxx -o $*Dict.o
		$(CXX) $(INCLUDES) $(CXXFLAGS) -c $*Dict.cxx -o obj/$*Dict.o
		rm -f $*Dict.cxx $*Dict.h 

obj/%.o : %.cxx
	@echo "Compiling $@"
	@$(CXX) $(CXXFLAGS) -O2 -c $< -MD -o $@ $(INCLUDES)

obj/%.o : %.cc
	@echo "Compiling $@"
	@$(CXX) $(CXXFLAGS) -O2 -c $< -MD -o $@ $(INCLUDES)

obj/%.o : %.C
	@echo "Compiling $@"
	@$(CXX) $(CXXFLAGS) -O2 -c $< -MD -o $@ $(INCLUDES)

clean:
	@echo "Cleaning $<..."
	rm -fr *~ obj/*.o */*~ *_Dict.* *.a 
	@echo "Done"
