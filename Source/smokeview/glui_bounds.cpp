#define CPP
#include "options.h"

#include <stdio.h>
#include <string.h>
#include GLUT_H
#include <math.h>

#include "smokeviewvars.h"
#include "MALLOC.h"

int nevacloaded, nplot3dloaded, nsmoke3dloaded, nisoloaded, nsliceloaded, nvsliceloaded, npartloaded, npatchloaded;

GLUI_Rollout *ROLLOUT_slice_bound=NULL;
GLUI_Rollout *ROLLOUT_slice_chop=NULL;
GLUI_Rollout *ROLLOUT_part_bound=NULL;
GLUI_Rollout *ROLLOUT_part_chop=NULL;
GLUI_Rollout *ROLLOUT_zone_bound=NULL;

#ifdef pp_MEMDEBUG
#define MEMCHECK 1
#endif

#define SMOOTH_SURFACES 402
#define SORT_SURFACES 401
#define ISO_SURFACE 1
#define ISO_OUTLINE 2
#define ISO_POINTS 3
#define ISO_COLORS 4
#define ISO_LEVEL 5
#define ISO_TRANSPARENCY 6
#define GLOBAL_ALPHA 7
#define COLORTABLE_LIST 8
#define SETVALMIN 1
#define SETVALMAX 2
#define VALMIN 3
#define VALMAX 4
#define FILETYPEINDEX 5
#define FILEUPDATE 6
#define FILERELOAD 7
#define FILEUPDATEDATA 8
#define UPDATEPLOT 10
#define PLOTISO 11
#define SHOWCHAR 12
#define CHOPVALMIN 13
#define CHOPVALMAX 14
#define SETCHOPMINVAL 15
#define SETCHOPMAXVAL 16
#define CHOPUPDATE 17
#define FRAMELOADING 18
#define STREAKLENGTH 19
#define TRACERS 21
#define PLOTISOTYPE 22
#define CACHE_BOUNDARYDATA 23
#define SHOWPATCH_BOTH 24
#define HIDEPATCHSURFACE 25
#define DATA_transparent 26
#define ALLFILERELOAD 27
#define UNLOAD_QDATA 203
#define SET_TIME 204
#define TBOUNDS 205
#define TBOUNDS_USE 206
#define RELOAD_ALL_DATA 207
#define RELOAD_INCREMENTAL_DATA 215
#define SHOW_EVAC_SLICES 208
#define DATA_EVAC_COLORING 209
#define SLICE_VECTORSKIP 210
#define PLOT3D_VECTORSKIP 211
#define UPDATE_SLICEDUPS 212
#define UPDATE_HISTOGRAM 213
#define INIT_HISTOGRAM 214

#define SCRIPT_START 31
#define SCRIPT_STOP 32
#define SCRIPT_LIST 33
#define SCRIPT_SAVEINI 34
#define SCRIPT_EDIT_INI 35
#define SCRIPT_SETSUFFIX 36
#define SCRIPT_RUNSCRIPT 37
#define SCRIPT_LOADINI 38
#define SCRIPT_RENDER 41
#define SCRIPT_RENDER_SUFFIX 42
#define SCRIPT_RENDER_DIR 43
#define SCRIPT_STEP_NOW 44
#define SCRIPT_CANCEL_NOW 45

#define ZONEVALMIN 50
#define ZONEVALMAX 51
#define SETZONEVALMIN 52
#define SETZONEVALMAX 53

#define SAVE_SETTINGS 99
#define CLOSE_BOUNDS 98
#define COMPRESS_FILES 97
#define OVERWRITE 96
#define COMPRESS_AUTOLOADED 91
#define ERASE 95
#define STARTUP 94
#define SAVE_FILE_LIST 93
#define LOAD_FILES 92
#define COLORBAR_EXTREME2 109
#define TRANSPARENTLEVEL 110
#define COLORBAR_LIST2 112
#define COLORBAR_SMOOTH 113
#define RESEARCH_MODE 114
#define COLORBAND 115
#define SLICE_IN_OBST 116

#define UPDATE_VECTOR 101
#define UPDATE_VECTOR_FROM_SMV 102

#define TRUNCATE_BOUNDS 1
#define DONT_TRUNCATE_BOUNDS 0
#define UPDATE_BOUNDS 1
#define RELOAD_BOUNDS 0
#define UPDATERELOAD_BOUNDS 2

#define LINE_CONTOUR_VALUE 301
#define UPDATE_LINE_CONTOUR_VALUE 302

#define FILESHOW_particle    10
#define FILESHOW_slice       11
#define FILESHOW_vslice      12
#define FILESHOW_boundary    13
#define FILESHOW_3dsmoke     14
#define FILESHOW_isosurface  15
#define FILESHOW_evac 19
#define FILESHOW_plot3d 16
#define BOUNDARY_LOAD_INCREMENTAL 16
#define SLICE_LOAD_INCREMENTAL 17

GLUI *glui_bounds=NULL;

GLUI_Button *BUTTON_globalalpha = NULL;
GLUI_Button *BUTTON_updatebound = NULL;
GLUI_Button *BUTTON_reloadbound=NULL;
GLUI_Button *BUTTON_compress=NULL;
GLUI_Button *BUTTON_step=NULL;
GLUI_Button *BUTTON_script_stop=NULL;
GLUI_Button *BUTTON_script_start=NULL;
GLUI_Button *BUTTON_script_saveini=NULL;
GLUI_Button *BUTTON_script_render=NULL;
GLUI_Button *BUTTON_update_line_contour=NULL;
GLUI_Button *BUTTON_ini_load=NULL;
GLUI_Button *BUTTON_script_setsuffix=NULL;
GLUI_Button *BUTTON_script_runscript=NULL;
GLUI_Button *BUTTON_SETTIME=NULL;
GLUI_Button *BUTTON_EVAC = NULL;
GLUI_Button *BUTTON_PART = NULL;
GLUI_Button *BUTTON_SLICE = NULL;
GLUI_Button *BUTTON_VSLICE = NULL;
GLUI_Button *BUTTON_PLOT3D = NULL;
GLUI_Button *BUTTON_3DSMOKE = NULL;
GLUI_Button *BUTTON_BOUNDARY = NULL;
GLUI_Button *BUTTON_ISO = NULL;

GLUI_Listbox *LIST_colortable = NULL;

#ifdef pp_MEMDEBUG
GLUI_Rollout *ROLLOUT_memcheck=NULL;
#endif
GLUI_Rollout *ROLLOUT_iso_settings;
GLUI_Rollout *ROLLOUT_iso_color;
GLUI_Rollout *ROLLOUT_script = NULL;
GLUI_Rollout *ROLLOUT_config = NULL;
GLUI_Rollout *ROLLOUT_boundary = NULL;
GLUI_Rollout *ROLLOUT_autoload=NULL;
GLUI_Rollout *ROLLOUT_compress=NULL;
GLUI_Rollout *ROLLOUT_plot3d=NULL,*ROLLOUT_part=NULL,*ROLLOUT_slice=NULL,*ROLLOUT_bound=NULL,*ROLLOUT_iso=NULL;
GLUI_Rollout *ROLLOUT_iso_colors = NULL;
GLUI_Rollout *ROLLOUT_smoke3d=NULL,*ROLLOUT_volsmoke3d=NULL;
GLUI_Rollout *ROLLOUT_time=NULL,*ROLLOUT_colorbar=NULL;
GLUI_Rollout *ROLLOUT_outputpatchdata=NULL;
GLUI_Rollout *ROLLOUT_filebounds = NULL;
GLUI_Rollout *ROLLOUT_showhide = NULL;
GLUI_Rollout *ROLLOUT_slice_average = NULL;
GLUI_Rollout *ROLLOUT_slice_histogram = NULL;
GLUI_Rollout *ROLLOUT_slice_vector = NULL;
GLUI_Rollout *ROLLOUT_line_contour = NULL;
GLUI_Rollout *ROLLOUT_slicedups = NULL;
GLUI_Rollout *ROLLOUT_vector = NULL;
GLUI_Rollout *ROLLOUT_isosurface = NULL;

GLUI_Panel *PANEL_sliceshow=NULL;
GLUI_Panel *PANEL_slicedup = NULL;
GLUI_Panel *PANEL_vectorslicedup = NULL;
GLUI_Panel *PANEL_iso_eachlevel = NULL;
GLUI_Panel *PANEL_iso_alllevels = NULL;
GLUI_Panel *PANEL_files = NULL;
GLUI_Panel *PANEL_bounds = NULL;
GLUI_Panel *PANEL_zone_a=NULL, *PANEL_zone_b=NULL;
GLUI_Panel *PANEL_evac_direction=NULL;
GLUI_Panel *PANEL_pan1=NULL;
GLUI_Panel *PANEL_pan2=NULL;
GLUI_Panel *PANEL_pan3=NULL;
GLUI_Panel *PANEL_run=NULL;
GLUI_Panel *PANEL_record=NULL;
GLUI_Panel *PANEL_script1=NULL;
GLUI_Panel *PANEL_script1a=NULL;
GLUI_Panel *PANEL_script1b=NULL;
GLUI_Panel *PANEL_script1c=NULL;
GLUI_Panel *PANEL_script2a=NULL;
GLUI_Panel *PANEL_script2b=NULL;
GLUI_Panel *PANEL_script3=NULL;
GLUI_Panel *PANEL_transparency2=NULL;
GLUI_Panel *PANEL_time2=NULL;
GLUI_Panel *PANEL_time1a=NULL;
GLUI_Panel *PANEL_time2a=NULL;
GLUI_Panel *PANEL_time2b=NULL;
GLUI_Panel *PANEL_time2c=NULL;
GLUI_Panel *PANEL_outputpatchdata=NULL;

GLUI_Spinner *SPINNER_histogram_width_factor = NULL;
GLUI_Spinner *SPINNER_histogram_nbuckets=NULL;
GLUI_Spinner *SPINNER_iso_level = NULL;
GLUI_Spinner *SPINNER_iso_colors[4];
GLUI_Spinner *SPINNER_iso_transparency;
GLUI_Spinner *SPINNER_transparent_level = NULL;
GLUI_Spinner *SPINNER_line_contour_num=NULL;
GLUI_Spinner *SPINNER_line_contour_width=NULL;
GLUI_Spinner *SPINNER_line_contour_min=NULL;
GLUI_Spinner *SPINNER_line_contour_max=NULL;
GLUI_Spinner *SPINNER_timebounds=NULL;
GLUI_Spinner *SPINNER_tload_begin=NULL;
GLUI_Spinner *SPINNER_tload_end=NULL;
GLUI_Spinner *SPINNER_tload_skip=NULL;
GLUI_Spinner *SPINNER_plot3d_vectorpointsize=NULL,*SPINNER_plot3d_vectorlinewidth=NULL,*SPINNER_plot3d_vectorlinelength=NULL;
GLUI_Spinner *SPINNER_sliceaverage=NULL;
GLUI_Spinner *SPINNER_smoke3dzipstep=NULL;
GLUI_Spinner *SPINNER_slicezipstep=NULL;
GLUI_Spinner *SPINNER_isozipstep=NULL;
GLUI_Spinner *SPINNER_boundzipstep=NULL;
GLUI_Spinner *SPINNER_partstreaklength=NULL;
GLUI_Spinner *SPINNER_partpointsize=NULL;
GLUI_Spinner *SPINNER_isopointsize=NULL;
GLUI_Spinner *SPINNER_isolinewidth=NULL;
GLUI_Spinner *SPINNER_plot3dpointsize=NULL;
GLUI_Spinner *SPINNER_plot3dlinewidth=NULL;
GLUI_Spinner *SPINNER_streaklinewidth=NULL;
GLUI_Spinner *SPINNER_vectorpointsize=NULL;
GLUI_Spinner *SPINNER_vectorlinewidth=NULL;
GLUI_Spinner *SPINNER_vectorlinelength=NULL;
GLUI_Spinner *SPINNER_slicevectorskip=NULL;
GLUI_Spinner *SPINNER_plot3dvectorskip=NULL;

GLUI_Listbox *LIST_scriptlist=NULL;
GLUI_Listbox *LIST_ini_list=NULL;

GLUI_EditText *EDIT_zone_min=NULL, *EDIT_zone_max=NULL;
GLUI_EditText *EDIT_ini=NULL;
GLUI_EditText *EDIT_renderdir=NULL;
GLUI_EditText *EDIT_rendersuffix=NULL;
GLUI_EditText *EDIT_slice_min=NULL, *EDIT_slice_max=NULL;
GLUI_EditText *EDIT_slice_chopmin=NULL, *EDIT_slice_chopmax=NULL;
GLUI_EditText *EDIT_patch_chopmin=NULL, *EDIT_patch_chopmax=NULL;
GLUI_EditText *EDIT_part_chopmin=NULL, *EDIT_part_chopmax=NULL;
GLUI_EditText *EDIT_patch_min=NULL, *EDIT_patch_max=NULL;
GLUI_EditText *EDIT_part_min=NULL, *EDIT_part_max=NULL;
GLUI_EditText *EDIT_p3_min=NULL, *EDIT_p3_max=NULL;
GLUI_EditText *EDIT_p3_chopmin=NULL, *EDIT_p3_chopmax=NULL;

#ifdef pp_FSEEK
GLUI_Checkbox *CHECKBOX_boundary_load_incremental=NULL;
GLUI_Checkbox *CHECKBOX_slice_load_incremental=NULL;
#endif
GLUI_Checkbox *CHECKBOX_histogram_show_numbers=NULL;
GLUI_Checkbox *CHECKBOX_histogram_show_graph=NULL;
GLUI_Checkbox *CHECKBOX_histogram_show_outline=NULL;
GLUI_Checkbox *CHECKBOX_color_vector_black = NULL;
GLUI_Checkbox *CHECKBOX_show_node_slices_and_vectors=NULL;
GLUI_Checkbox *CHECKBOX_show_cell_slices_and_vectors=NULL;
GLUI_Checkbox *CHECKBOX_cache_boundarydata=NULL;
GLUI_Checkbox *CHECKBOX_showpatch_both=NULL;
GLUI_Checkbox *CHECKBOX_showchar=NULL, *CHECKBOX_showonlychar;
GLUI_Checkbox *CHECKBOX_show_iso_solid=NULL;
GLUI_Checkbox *CHECKBOX_show_iso_outline=NULL;
GLUI_Checkbox *CHECKBOX_show_iso_verts=NULL;
GLUI_Checkbox *CHECKBOX_defer=NULL;
GLUI_Checkbox *CHECKBOX_script_step=NULL;
GLUI_Checkbox *CHECKBOX_show_evac_slices=NULL;
GLUI_Checkbox *CHECKBOX_constant_coloring=NULL;
GLUI_Checkbox *CHECKBOX_show_evac_color=NULL;
GLUI_Checkbox *CHECKBOX_data_coloring=NULL;
GLUI_Checkbox *CHECKBOX_transparentflag2=NULL;
GLUI_Checkbox *CHECKBOX_sort2=NULL;
GLUI_Checkbox *CHECKBOX_smooth2=NULL;
GLUI_Checkbox *CHECKBOX_overwrite_all=NULL;
GLUI_Checkbox *CHECKBOX_compress_autoloaded=NULL;
GLUI_Checkbox *CHECKBOX_erase_all=NULL;
GLUI_Checkbox *CHECKBOX_multi_task=NULL;
GLUI_Checkbox *CHECKBOX_slice_setchopmin=NULL;
GLUI_Checkbox *CHECKBOX_slice_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_p3_setchopmin=NULL, *CHECKBOX_p3_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_patch_setchopmin=NULL, *CHECKBOX_patch_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_part_setchopmin=NULL, *CHECKBOX_part_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_showtracer=NULL;
GLUI_Checkbox *CHECKBOX_cellcenter_slice_interp=NULL;
GLUI_Checkbox *CHECKBOX_skip_subslice=NULL;
GLUI_Checkbox *CHECKBOX_turb_slice=NULL;
GLUI_Checkbox *CHECKBOX_average_slice=NULL;
GLUI_Checkbox *CHECKBOX_cache_qdata=NULL;
GLUI_Checkbox *CHECKBOX_use_tload_begin=NULL;
GLUI_Checkbox *CHECKBOX_use_tload_end=NULL;
GLUI_Checkbox *CHECKBOX_use_tload_skip=NULL;
GLUI_Checkbox *CHECKBOX_research_mode=NULL;

GLUI_RadioGroup *RADIO_show_slice_in_obst=NULL;
GLUI_RadioGroup *RADIO_slicedup = NULL;
GLUI_RadioGroup *RADIO_vectorslicedup = NULL;
GLUI_RadioGroup *RADIO_histogram_static=NULL;
GLUI_RadioGroup *RADIO_showhide = NULL;
GLUI_RadioGroup *RADIO_contour_type = NULL;
GLUI_RadioGroup *RADIO_zone_setmin=NULL, *RADIO_zone_setmax=NULL;
GLUI_RadioGroup *RADIO_bf=NULL, *RADIO_p3=NULL,*RADIO_slice=NULL;
GLUI_RadioGroup *RADIO_part5=NULL;
GLUI_RadioGroup *RADIO_plot3d_isotype=NULL;
GLUI_RadioGroup *RADIO_plot3d_display=NULL;
GLUI_RadioGroup *RADIO_slice_setmin=NULL, *RADIO_slice_setmax=NULL;
GLUI_RadioGroup *RADIO_patch_setmin=NULL, *RADIO_patch_setmax=NULL;
GLUI_RadioGroup *RADIO_part_setmin=NULL, *RADIO_part_setmax=NULL;
#ifdef pp_MEMDEBUG
GLUI_RadioGroup *RADIO_memcheck=NULL;
#endif
GLUI_RadioGroup *RADIO_p3_setmin=NULL, *RADIO_p3_setmax=NULL;

GLUI_RadioButton *RADIOBUTTON_plot3d_iso_hidden=NULL;
GLUI_RadioButton *RADIOBUTTON_zone_permin=NULL;
GLUI_RadioButton *RADIOBUTTON_zone_permax=NULL;

GLUI_StaticText *STATIC_bound_min_unit=NULL;
GLUI_StaticText *STATIC_bound_max_unit=NULL;
GLUI_StaticText *STATIC_slice_min_unit=NULL;
GLUI_StaticText *STATIC_slice_max_unit=NULL;
GLUI_StaticText *STATIC_part_min_unit=NULL;
GLUI_StaticText *STATIC_part_max_unit=NULL;
GLUI_StaticText *STATIC_plot3d_min_unit=NULL;
GLUI_StaticText *STATIC_plot3d_max_unit=NULL;
GLUI_StaticText *STATIC_bound_cmin_unit=NULL;
GLUI_StaticText *STATIC_bound_cmax_unit=NULL;
GLUI_StaticText *STATIC_slice_cmin_unit=NULL;
GLUI_StaticText *STATIC_slice_cmax_unit=NULL;
GLUI_StaticText *STATIC_part_cmin_unit=NULL;
GLUI_StaticText *STATIC_part_cmax_unit=NULL;
GLUI_StaticText *STATIC_plot3d_cmin_unit=NULL;
GLUI_StaticText *STATIC_plot3d_cmax_unit=NULL;

#define ZONE_ROLLOUT 0
#define SMOKE3D_ROLLOUT 1
#define BOUNDARY_ROLLOUT 2
#define ISO_ROLLOUT 3
#define PART_ROLLOUT 4
#define EVAC_ROLLOUT 5
#define PLOT3D_ROLLOUT 6
#define SLICE_ROLLOUT 7

#define ISO_ROLLOUT_SETTINGS 0
#define ISO_ROLLOUT_COLOR 1

#define SLICE_AVERAGE_ROLLOUT 0
#define SLICE_VECTOR_ROLLOUT 1
#define LINE_CONTOUR_ROLLOUT 2
#define SLICE_HISTOGRAM_ROLLOUT 3
#define SLICE_DUP_ROLLOUT 4

#define VECTOR_ROLLOUT 0
#define ISOSURFACE_ROLLOUT 1

#define LOAD_ROLLOUT 0
#define SHOWHIDE_ROLLOUT 1
#define COMPRESS_ROLLOUT 2
#define SCRIPT_ROLLOUT 3
#define CONFIG_ROLLOUT 4
#define FILEBOUNDS_ROLLOUT 5
#define TIME_ROLLOUT 6
#define MEMCHECK_ROLLOUT 7

procdata boundprocinfo[8], fileprocinfo[8], plot3dprocinfo[2], isoprocinfo[2];
procdata sliceprocinfo[5];
int nboundprocinfo = 0, nfileprocinfo = 0, nsliceprocinfo=0, nplot3dprocinfo=0, nisoprocinfo=0;

/* ------------------ LoadIncrementalCB1 ------------------------ */

extern "C" void LoadIncrementalCB1(int var){
  if(CHECKBOX_boundary_load_incremental!=NULL)CHECKBOX_boundary_load_incremental->set_int_val(load_incremental);
  if(CHECKBOX_slice_load_incremental!=NULL)CHECKBOX_slice_load_incremental->set_int_val(load_incremental);
}

/* ------------------ UpdateSliceDupDialog ------------------------ */

extern "C" void UpdateSliceDupDialog(void){
  if(RADIO_slicedup != NULL)RADIO_slicedup->set_int_val(slicedup_option);
  if(RADIO_vectorslicedup != NULL)RADIO_vectorslicedup->set_int_val(vectorslicedup_option);
}

/* ------------------ UpdateIsoControls ------------------------ */

void UpdateIsoControls(void){
  if(use_transparency_data==1){
    if(SPINNER_iso_colors[3] != NULL)SPINNER_iso_colors[3]->enable();
    if(SPINNER_iso_transparency != NULL)SPINNER_iso_transparency->enable();
    if(BUTTON_updatebound != NULL)BUTTON_updatebound->enable();
  }
  else{
    if(SPINNER_iso_colors[3] != NULL)SPINNER_iso_colors[3]->disable();
    if(SPINNER_iso_transparency != NULL)SPINNER_iso_transparency->disable();
    if(BUTTON_updatebound != NULL)BUTTON_updatebound->disable();
  }
}

/* ------------------ UpdateHistogramType ------------------------ */

extern "C" void UpdateHistogramType(void){
  RADIO_histogram_static->set_int_val(histogram_static);
  CHECKBOX_histogram_show_graph->set_int_val(histogram_show_graph);
  CHECKBOX_histogram_show_numbers->set_int_val(histogram_show_numbers);
  CHECKBOX_histogram_show_outline->set_int_val(histogram_show_outline);
}

/* ------------------ UpdateShowSliceInObst ------------------------ */

extern "C" void UpdateShowSliceInObst(void){
  RADIO_show_slice_in_obst->set_int_val(show_slice_in_obst);
}

/* ------------------ UpdateIsoColorlevel ------------------------ */

extern "C" void UpdateIsoColorlevel(void){
  IsoBoundCB(ISO_LEVEL);
  IsoBoundCB(ISO_COLORS);
}

/* ------------------ Plot3dRolloutCB ------------------------ */

void Plot3dRolloutCB(int var){
  ToggleRollout(plot3dprocinfo, nplot3dprocinfo, var);
}

/* ------------------ SliceRolloutCB ------------------------ */

void SliceRolloutCB(int var){
  ToggleRollout(sliceprocinfo, nsliceprocinfo, var);
}

/* ------------------ IsoRolloutCB ------------------------ */

void IsoRolloutCB(int var){
  ToggleRollout(isoprocinfo, nisoprocinfo, var);
}

/* ------------------ BoundRolloutCB ------------------------ */

void BoundRolloutCB(int var){
  ToggleRollout(boundprocinfo, nboundprocinfo, var);
}

/* ------------------ FileRolloutCB ------------------------ */

void FileRolloutCB(int var){
  ToggleRollout(fileprocinfo, nfileprocinfo, var);
}

/* ------------------ UpdateGluiZoneBounds ------------------------ */

extern "C" void UpdateGluiZoneBounds(void){
  if(EDIT_zone_min!=NULL)EDIT_zone_min->set_float_val(zonemin);
  if(EDIT_zone_max!=NULL)EDIT_zone_max->set_float_val(zonemax);
}
/* ------------------ UpdateGluiVecFactor ------------------------ */

extern "C" void UpdateGluiVecFactor(void){
  if(SPINNER_plot3d_vectorlinelength!=NULL)SPINNER_plot3d_vectorlinelength->set_float_val(vecfactor);
  if(SPINNER_vectorlinelength!=NULL)SPINNER_vectorlinelength->set_float_val(vecfactor);
}

/* ------------------ UpdateGluiPartUnits ------------------------ */

extern "C" void UpdateGluiPartUnits(void){
  if(STATIC_part_min_unit!=NULL){
    if(partmin_unit!=NULL){
      STATIC_part_min_unit->set_name((char *)partmin_unit);
    }
    else{
      STATIC_part_min_unit->set_name((char *)"");
    }
  }
  if(STATIC_part_cmin_unit!=NULL){
    if(partmin_unit!=NULL){
      STATIC_part_cmin_unit->set_name((char *)partmin_unit);
    }
    else{
      STATIC_part_cmin_unit->set_name((char *)"");
    }
  }
  if(STATIC_part_max_unit!=NULL){
    if(partmax_unit!=NULL){
      STATIC_part_max_unit->set_name((char *)partmax_unit);
    }
    else{
      STATIC_part_max_unit->set_name((char *)"");
    }
  }
  if(STATIC_part_cmax_unit!=NULL){
    if(partmax_unit!=NULL){
      STATIC_part_cmax_unit->set_name((char *)partmax_unit);
    }
    else{
      STATIC_part_cmax_unit->set_name((char *)"");
    }
  }
}

/* ------------------ UpdateGluiPlot3D_units ------------------------ */

extern "C" void UpdateGluiPlot3D_units(void){
  if(STATIC_plot3d_min_unit!=NULL&&plot3dmin_unit!=NULL){
    STATIC_plot3d_min_unit->set_name((char *)plot3dmin_unit);
  }
  if(STATIC_plot3d_max_unit!=NULL&&plot3dmax_unit!=NULL){
    STATIC_plot3d_max_unit->set_name((char *)plot3dmax_unit);
  }
  if(STATIC_plot3d_cmin_unit!=NULL&&plot3dmin_unit!=NULL){
    STATIC_plot3d_cmin_unit->set_name((char *)plot3dmin_unit);
  }
  if(STATIC_plot3d_cmax_unit!=NULL&&plot3dmax_unit!=NULL){
    STATIC_plot3d_cmax_unit->set_name((char *)plot3dmax_unit);
  }
}

/* ------------------ UpdateGluiSliceUnits ------------------------ */

extern "C" void UpdateGluiSliceUnits(void){
  if(STATIC_slice_min_unit!=NULL&&slicemin_unit!=NULL){
    STATIC_slice_min_unit->set_name((char *)slicemin_unit);
  }
  if(STATIC_slice_max_unit!=NULL&&slicemax_unit!=NULL){
    STATIC_slice_max_unit->set_name((char *)slicemax_unit);
  }
  if(STATIC_slice_cmin_unit!=NULL&&slicemin_unit!=NULL){
    STATIC_slice_cmin_unit->set_name((char *)slicemin_unit);
  }
  if(STATIC_slice_cmax_unit!=NULL&&slicemax_unit!=NULL){
    STATIC_slice_cmax_unit->set_name((char *)slicemax_unit);
  }
}

/* ------------------ UpdateGluiBoundaryUnits ------------------------ */

extern "C" void UpdateGluiBoundaryUnits(void){
  if(STATIC_bound_min_unit!=NULL&&patchmin_unit!=NULL){
    STATIC_bound_min_unit->set_name((char *)patchmin_unit);
  }
  if(STATIC_bound_max_unit!=NULL&&patchmax_unit!=NULL){
    STATIC_bound_max_unit->set_name((char *)patchmax_unit);
  }
  if(STATIC_bound_cmin_unit!=NULL&&patchmin_unit!=NULL){
    STATIC_bound_cmin_unit->set_name((char *)patchmin_unit);
  }
  if(STATIC_bound_cmax_unit!=NULL&&patchmax_unit!=NULL){
    STATIC_bound_cmax_unit->set_name((char *)patchmax_unit);
  }
}

/* ------------------ UpdateResearchMode ------------------------ */

extern "C" void UpdateResearchMode(void){
  SliceBoundCB(RESEARCH_MODE);
  if(CHECKBOX_research_mode!=NULL)CHECKBOX_research_mode->set_int_val(research_mode);
}
/* ------------------ UpdateScriptStop ------------------------ */

extern "C" void UpdateScriptStop(void){
  if(BUTTON_script_start!=NULL)BUTTON_script_start->enable();
  if(BUTTON_script_stop!=NULL)BUTTON_script_stop->disable();
  if(BUTTON_script_runscript!=NULL)BUTTON_script_runscript->enable();
  if(EDIT_renderdir!=NULL)EDIT_renderdir->enable();
}

/* ------------------ UpdateScriptStart ------------------------ */

extern "C" void UpdateScriptStart(void){
  if(BUTTON_script_start!=NULL)BUTTON_script_start->disable();
  if(BUTTON_script_stop!=NULL)BUTTON_script_stop->enable();
  if(BUTTON_script_runscript!=NULL)BUTTON_script_runscript->disable();
  if(EDIT_renderdir!=NULL)EDIT_renderdir->disable();
}

/* ------------------ UpdateDefer ------------------------ */

extern "C" void UpdateDefer(void){
  CHECKBOX_defer->set_int_val(defer_file_loading);
}

/* ------------------ UpdateScriptStep ------------------------ */

extern "C" void UpdateScriptStep(void){
  CHECKBOX_script_step->set_int_val(script_step);
  if(script_step==1){
    BUTTON_step->enable();
  }
  else{
    BUTTON_step->disable();
  }
}

/* ------------------ UpdateEvacParms ------------------------ */

extern "C" void UpdateEvacParms(void){
  if(CHECKBOX_show_evac_slices!=NULL)CHECKBOX_show_evac_slices->set_int_val(show_evac_slices);
  if(CHECKBOX_constant_coloring!=NULL)CHECKBOX_constant_coloring->set_int_val(constant_evac_coloring);
  if(CHECKBOX_data_coloring!=NULL)CHECKBOX_data_coloring->set_int_val(data_evac_coloring);
  if(CHECKBOX_show_evac_color!=NULL)CHECKBOX_show_evac_color->set_int_val(show_evac_colorbar);
}

/* ------------------ UpdateGluiPlot3D ------------------------ */

extern "C" void UpdateGluiPlot3D(void){
  Plot3DBoundCB(UNLOAD_QDATA);
}

/* ------------------ PartBoundCBInit ------------------------ */

extern "C" void PartBoundCBInit(void){
  PartBoundCB(FILETYPEINDEX);
}


/* ------------------ ColortableCompare ------------------------ */

int ColortableCompare(const void *arg1, const void *arg2){
  colortabledata *cti, *ctj;
  int i, j;

  i = *(int *)arg1;
  j = *(int *)arg2;

  cti = colortableinfo + i;
  ctj = colortableinfo + j;

  return(strcmp(cti->label, ctj->label));
}

/* ------------------ UpdateColorTableList ------------------------ */

extern "C" void UpdateColorTableList(int ncolortableinfo_old){
  int i, *order=NULL;

  if(LIST_colortable==NULL)return;
  for(i = -1; i<ncolortableinfo_old; i++){
    LIST_colortable->delete_item(i);
  }

  if(ncolortableinfo>0){
    NewMemory((void **)&order, ncolortableinfo*sizeof(int));
    for(i = 0; i < ncolortableinfo; i++){
      order[i] = i;
    }
    qsort((int *)order, (size_t)ncolortableinfo, sizeof(int), ColortableCompare);
  }


  for(i = -1; i<ncolortableinfo; i++){
    if(i==-1){
      LIST_colortable->add_item(i, "Custom");
    }
    else{
      colortabledata *cti;

      cti = colortableinfo+order[i];
      LIST_colortable->add_item(i, cti->label);
    }
  }
  if(ncolortableinfo>0){
    FREEMEMORY(order);
  }
}

/* ------------------ FileShowCB ------------------------ */

extern "C" void FileShowCB(int var){
  updatemenu = 1;
  switch(var){
  case  FILESHOW_plot3d:
    switch(showhide_option){
    case SHOWALL_FILES:
    case SHOWONLY_FILE:
      Plot3DShowMenu(SHOWALL_PLOT3D);
      break;
    case HIDEALL_FILES:
      Plot3DShowMenu(HIDEALL_PLOT3D);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case FILESHOW_evac:
    switch(showhide_option){
    case SHOWALL_FILES:
      EvacShowMenu(SHOWALL_EVAC);
      break;
    case SHOWONLY_FILE:
      EvacShowMenu(SHOWALL_EVAC);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(nsliceloaded != 0)ShowHideSliceMenu(HIDEALL_SLICE);
      if(nvsliceloaded != 0)ShowVSliceMenu(HIDEALL_VSLICE);
      if(npatchloaded != 0)ShowBoundaryMenu(HIDEALL_BOUNDARY);
      break;
    case HIDEALL_FILES:
      EvacShowMenu(HIDEALL_EVAC);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_particle:
    switch(showhide_option){
    case SHOWALL_FILES:
      ParticleShowMenu(SHOWALL_PARTICLE);
      break;
    case SHOWONLY_FILE:
      ParticleShowMenu(SHOWALL_PARTICLE);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(nsliceloaded != 0)ShowHideSliceMenu(HIDEALL_SLICE);
      if(nvsliceloaded != 0)ShowVSliceMenu(HIDEALL_VSLICE);
      if(npatchloaded != 0)ShowBoundaryMenu(HIDEALL_BOUNDARY);
      break;
    case HIDEALL_FILES:
      ParticleShowMenu(HIDEALL_PARTICLE);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_slice:
    switch(showhide_option){
    case SHOWALL_FILES:
      ShowHideSliceMenu(SHOWALL_SLICE);
      break;
    case SHOWONLY_FILE:
      ShowHideSliceMenu(SHOWALL_SLICE);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nvsliceloaded != 0)ShowVSliceMenu(HIDEALL_VSLICE);
      if(npatchloaded != 0)ShowBoundaryMenu(HIDEALL_BOUNDARY);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      break;
    case HIDEALL_FILES:
      ShowHideSliceMenu(HIDEALL_SLICE);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_vslice:
    switch(showhide_option){
    case SHOWALL_FILES:
      ShowVSliceMenu(SHOWALL_VSLICE);
      break;
    case SHOWONLY_FILE:
      ShowVSliceMenu(SHOWALL_VSLICE);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(npatchloaded != 0)ShowBoundaryMenu(HIDEALL_BOUNDARY);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nsliceloaded != 0)ShowHideSliceMenu(HIDEALL_SLICE);
      break;
    case HIDEALL_FILES:
      ShowHideSliceMenu(HIDEALL_SLICE);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_boundary:
    switch(showhide_option){
    case SHOWALL_FILES:
      ShowBoundaryMenu(SHOWALL_BOUNDARY);
      break;
    case SHOWONLY_FILE:
      ShowBoundaryMenu(SHOWALL_BOUNDARY);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nvsliceloaded != 0)ShowVSliceMenu(HIDEALL_VSLICE);
      if(nsliceloaded != 0)ShowHideSliceMenu(HIDEALL_SLICE);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      break;
    case HIDEALL_FILES:
      ShowBoundaryMenu(HIDEALL_BOUNDARY);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_3dsmoke:
    switch(showhide_option){
    case SHOWALL_FILES:
      Smoke3DShowMenu(SHOWALL_SMOKE3D);
      break;
    case SHOWONLY_FILE:
      Smoke3DShowMenu(SHOWALL_SMOKE3D);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(npatchloaded != 0)ShowBoundaryMenu(HIDEALL_BOUNDARY);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nvsliceloaded != 0)ShowVSliceMenu(HIDEALL_VSLICE);
      if(nsliceloaded != 0)ShowHideSliceMenu(HIDEALL_SLICE);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      break;
    case HIDEALL_FILES:
      Smoke3DShowMenu(HIDEALL_SMOKE3D);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_isosurface:
    switch(showhide_option){
    case SHOWALL_FILES:
      IsoShowMenu(SHOWALL_ISO);
      break;
    case SHOWONLY_FILE:
      IsoShowMenu(SHOWALL_ISO);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(npatchloaded != 0)ShowBoundaryMenu(HIDEALL_BOUNDARY);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nvsliceloaded != 0)ShowVSliceMenu(HIDEALL_VSLICE);
      if(nsliceloaded != 0)ShowHideSliceMenu(HIDEALL_SLICE);
      break;
    case HIDEALL_FILES:
      IsoShowMenu(HIDEALL_ISO);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  default:
    break;
  }
}

#ifdef pp_MEMDEBUG

/* ------------------ MemcheckCB ------------------------ */

void MemcheckCB(int var){
  switch(var){
  case MEMCHECK:
    set_memcheck(list_memcheck_index);
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}
#endif

/* ------------------ BoundsDlgCB ------------------------ */

void BoundsDlgCB(int var){
  switch(var){
  case CLOSE_BOUNDS:
    glui_bounds->hide();
    updatemenu = 1;
    break;
  case SAVE_SETTINGS:
    WriteIni(LOCAL_INI, NULL);
    break;
  case COMPRESS_FILES:
    PRINTF("compressing\n");
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ BoundBoundCB ------------------------ */

void BoundBoundCB(int var){
  int i;

  switch(var){
  case SHOWPATCH_BOTH:
    updatefacelists = 1;
    updatehiddenfaces = 1;
    break;
  case CACHE_BOUNDARYDATA:
    if(cache_boundarydata == 0){
      BUTTON_updatebound->disable();
    }
    else{
      BUTTON_updatebound->enable();
    }
    break;
  case VALMAX:
  case VALMIN:
    break;
  case HIDEPATCHSURFACE:
    updatefacelists = 1;
    break;
  case FRAMELOADING:
    boundframestep = boundframeskip + 1;
    boundzipstep = boundzipskip + 1;
    updatemenu = 1;
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    UpdateChopColors();
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    switch(setpatchchopmin){
    case DISABLE:
      EDIT_patch_chopmin->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmin->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    UpdateHideBoundarySurface();
    break;
  case SETCHOPMAXVAL:
    UpdateChopColors();
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    switch(setpatchchopmax){
    case DISABLE:
      EDIT_patch_chopmax->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    UpdateHideBoundarySurface();
    break;
  case CHOPVALMIN:
    ASSERT(EDIT_patch_min != NULL);
    EDIT_patch_min->set_float_val(patchmin);
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    UpdateChopColors();
    break;
  case CHOPVALMAX:
    ASSERT(EDIT_patch_max != NULL);
    EDIT_patch_max->set_float_val(patchmax);
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    UpdateChopColors();
    break;
  case SHOWCHAR:
    if(CHECKBOX_showchar != NULL&&CHECKBOX_showonlychar != NULL){
      if(vis_threshold == 1){
        CHECKBOX_showonlychar->enable();
      }
      else{
        CHECKBOX_showonlychar->disable();
      }
    }
    updatemenu = 1;
    updatefacelists = 1;
    break;
  case FILETYPEINDEX:
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index_old]);
    Global2LocalBoundaryBounds(patchlabellist[list_patch_index]);

    EDIT_patch_min->set_float_val(patchmin);
    EDIT_patch_max->set_float_val(patchmax);
    EDIT_patch_chopmin->set_float_val(patchchopmin);
    EDIT_patch_chopmax->set_float_val(patchchopmax);

    BoundBoundCB(SETVALMIN);
    BoundBoundCB(SETVALMAX);
    if(RADIO_patch_setmin != NULL)RADIO_patch_setmin->set_int_val(setpatchmin);
    if(RADIO_patch_setmax != NULL)RADIO_patch_setmax->set_int_val(setpatchmax);
    if(CHECKBOX_patch_setchopmin != NULL)CHECKBOX_patch_setchopmin->set_int_val(setpatchchopmin);
    if(CHECKBOX_patch_setchopmax != NULL)CHECKBOX_patch_setchopmax->set_int_val(setpatchchopmax);

    switch(setpatchchopmin){
    case DISABLE:
      EDIT_patch_chopmin->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmin->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    switch(setpatchchopmax){
    case DISABLE:
      EDIT_patch_chopmax->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }

    list_patch_index_old = list_patch_index;
    UpdateHideBoundarySurface();
    break;
  case SETVALMIN:
    switch(setpatchmin){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      EDIT_patch_min->disable();
      break;
    case SET_MIN:
      EDIT_patch_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    BoundBoundCB(FILEUPDATE);
    break;
  case SETVALMAX:
    switch(setpatchmax){
    case PERCENTILE_MAX:
    case GLOBAL_MAX:
      EDIT_patch_max->disable();
      break;
    case SET_MAX:
      EDIT_patch_max->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    BoundBoundCB(FILEUPDATE);
    break;
  case FILEUPDATE:
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    break;
  case FILEUPDATEDATA:
    UpdateAllBoundaryColors();
    break;
  case FILERELOAD:
    BoundBoundCB(FILEUPDATE);
    for(i = 0;i < npatchinfo;i++){
      patchdata *patchi;

      patchi = patchinfo + i;
      if(patchi->loaded == 0)continue;
      LoadBoundaryMenu(i);
    }
    EDIT_patch_min->set_float_val(patchmin);
    EDIT_patch_max->set_float_val(patchmax);
    break;
  case COMPRESS_FILES:
    CompressSVZip();
    break;
  case COMPRESS_AUTOLOADED:
    updatemenu = 1;
    break;
  case OVERWRITE:
    if(overwrite_all == 1){
      CHECKBOX_erase_all->set_int_val(0);
    }
    updatemenu = 1;
    break;
  case ERASE:
    if(erase_all == 1){
      CHECKBOX_overwrite_all->set_int_val(0);
    }
    updatemenu = 1;
    break;
  case STARTUP:
    BoundsDlgCB(SAVE_SETTINGS);
    break;
  case SAVE_FILE_LIST:
    Set3DSmokeStartup();
    BoundsDlgCB(SAVE_SETTINGS);
    break;
  case LOAD_FILES:
    LoadFiles();
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ Smoke3dBoundCB ------------------------ */

void Smoke3dBoundCB(int var){
  switch(var){
  case FRAMELOADING:
    smoke3dframestep = smoke3dframeskip + 1;
    smoke3dzipstep = smoke3dzipskip + 1;
    updatemenu = 1;
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ TimeBoundCB ------------------------ */

void TimeBoundCB(int var){

  updatemenu = 1;
  switch(var){
  case SET_TIME:
    SetTimeVal(glui_time);
    break;
  case TBOUNDS:
    if(use_tload_begin == 1 || use_tload_end == 1 || use_tload_skip == 1){
      UpdateTBounds();
    }
    break;
  case TBOUNDS_USE:
    if(use_tload_begin == 1){
      SPINNER_tload_begin->enable();
    }
    else{
      SPINNER_tload_begin->disable();
    }
    if(use_tload_end == 1){
      SPINNER_tload_end->enable();
    }
    else{
      SPINNER_tload_end->disable();
    }
    if(use_tload_skip == 1){
      SPINNER_tload_skip->enable();
    }
    else{
      SPINNER_tload_skip->disable();
    }
    UpdateTBounds();
    break;
  case RELOAD_ALL_DATA:
    ReloadMenu(RELOAD_ALL_NOW);
    break;
  case RELOAD_INCREMENTAL_DATA:
    ReloadMenu(RELOAD_INCREMENTAL_NOW);
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ ScriptCB ------------------------ */

void ScriptCB(int var){
  char label[1024];
  char *name;
  int id;
  int len, i;
  int set_renderlabel;

  switch(var){
  case SCRIPT_STEP_NOW:
    Keyboard('^', FROM_SMOKEVIEW);
    break;
  case SCRIPT_CANCEL_NOW:
    current_script_command = NULL;
    runscript = 0;
    first_frame_index = 0;
    skip_render_frames = 0;
    script_startframe = -1;
    script_skipframe = -1;
    script_step = 0;
    GluiScriptEnable();
    rendering_status = RENDER_OFF;
    break;
  case SCRIPT_RENDER_DIR:
    strcpy(label, script_renderdir);
    TrimBack(label);
    name = TrimFront(label);
    set_renderlabel = 0;
    if(name != NULL&&strlen(name) != strlen(script_renderdir)){
      strcpy(script_renderdir, name);
      set_renderlabel = 1;
    }
    name = script_renderdir;
    len = strlen(script_renderdir);
    if(len == 0)break;
    for(i = 0;i < len;i++){
#ifdef WIN32
      if(name[i] == '/'){
        set_renderlabel = 1;
        name[i] = '\\';
      }
#else
      if(name[i] == '\\'){
        set_renderlabel = 1;
        name[i] = '/';
      }
#endif
    }
#ifdef WIN32
    if(name[len - 1] != '\\'){
      set_renderlabel = 1;
      strcat(name, dirseparator);
    }
#else
    if(name[len - 1] != '/'){
      set_renderlabel = 1;
      strcat(name, dirseparator);
    }
#endif
    if(set_renderlabel == 1){
      EDIT_renderdir->set_text(script_renderdir);
    }
    break;
  case SCRIPT_RENDER:
    Keyboard('r', FROM_SMOKEVIEW);
    break;
  case SCRIPT_RENDER_SUFFIX:
  {
    char *suffix;

    TrimBack(script_renderfilesuffix);
    suffix = TrimFront(script_renderfilesuffix);
    strcpy(script_renderfile, "");
    if(strlen(suffix) > 0){
      strcpy(script_renderfile, fdsprefix);
      strcat(script_renderfile, "_");
      strcat(script_renderfile, suffix);
      strcpy(label, _d("Render: "));
      strcat(label, script_renderfile);
    }
    else{
      strcpy(label, _d("Render"));
    }
    BUTTON_script_render->set_name(label);
  }
  break;
  case SCRIPT_START:
    ScriptMenu(SCRIPT_START_RECORDING);
    break;
  case SCRIPT_STOP:
    ScriptMenu(SCRIPT_STOP_RECORDING);
    break;
  case SCRIPT_RUNSCRIPT:
    name = 5 + BUTTON_script_runscript->name;
    PRINTF("running script: %s\n", name);
    ScriptMenu(LIST_scriptlist->get_int_val());
    break;
  case SCRIPT_LIST:
    id = LIST_scriptlist->get_int_val();
    name = GetScriptFileName(id);
    if(name != NULL&&strlen(name) > 0){
      strcpy(label, _d("Run: "));
      strcat(label, name);
      BUTTON_script_runscript->set_name(label);
    }
    break;
  case SCRIPT_SAVEINI:
    name = 5 + BUTTON_script_saveini->name;
    if(strlen(name) > 0){
      inifiledata *inifile;

      strcpy(script_filename, name);
      inifile = InsertIniFile(name);
      WriteIni(SCRIPT_INI, script_filename);
      if(inifile != NULL&&LIST_ini_list != NULL){
        LIST_ini_list->add_item(inifile->id, inifile->file);
      }
    }
    WriteIni(LOCAL_INI, NULL);
    break;
  case SCRIPT_LOADINI:
  {
    char *ini_filename;

    id = LIST_ini_list->get_int_val();
    ini_filename = GetIniFileName(id);
    if(ini_filename == NULL)break;
    if(strcmp(ini_filename, caseini_filename) == 0){
      ReadIni(NULL);
    }
    else if(id >= 0){
      char *script_filename2;

      if(strlen(ini_filename) == 0)break;
      script_filename2 = script_filename;
      strcpy(script_filename, ini_filename);
      windowresized = 0;
      ReadIni(script_filename2);
    }
    if(scriptoutstream != NULL){
      fprintf(scriptoutstream, "LOADINIFILE\n");
      fprintf(scriptoutstream, " %s\n", ini_filename);
    }
  }
  break;
  case SCRIPT_STEP:
    UpdateScriptStep();
    updatemenu = 1;
    break;
  case SCRIPT_FILE_LOADING:
    updatemenu = 1;
    break;
  case SCRIPT_EDIT_INI:
    strcpy(label, _d("Save "));
    strcat(label, fdsprefix);
    TrimBack(script_inifile_suffix);
    if(strlen(script_inifile_suffix) > 0){
      strcat(label, "_");
      strcat(label, script_inifile_suffix);
    }
    strcat(label, ".ini");
    BUTTON_script_saveini->set_name(label);
    break;
  case SCRIPT_SETSUFFIX:
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ BoundMenu ------------------------ */

void BoundMenu(GLUI_Rollout **bound_rollout, GLUI_Rollout **chop_rollout, GLUI_Panel *PANEL_panel, char *button_title,
  GLUI_EditText **EDIT_con_min, GLUI_EditText **EDIT_con_max,
  GLUI_RadioGroup **RADIO_con_setmin, GLUI_RadioGroup **RADIO_con_setmax,
  GLUI_Checkbox **CHECKBOX_con_setchopmin, GLUI_Checkbox **CHECKBOX_con_setchopmax,
  GLUI_EditText **EDIT_con_chopmin, GLUI_EditText **EDIT_con_chopmax,
  GLUI_StaticText **STATIC_con_min_unit, GLUI_StaticText **STATIC_con_max_unit,
  GLUI_StaticText **STATIC_con_cmin_unit, GLUI_StaticText **STATIC_con_cmax_unit,
  GLUI_Button **BUTTON_update, GLUI_Button **BUTTON_reload,

  int *setminval, int *setmaxval,
  float *minval, float *maxval,
  int *setchopminval, int *setchopmaxval,
  float *chopminval, float *chopmaxval,
  int updatebounds,
  int truncatebounds,
  GLUI_Update_CB FILE_CB){

  GLUI_Panel *PANEL_a, *PANEL_b, *PANEL_c;
  GLUI_Rollout *PANEL_e = NULL, *PANEL_g = NULL;
  GLUI_Panel *PANEL_f = NULL, *PANEL_h = NULL;

  PANEL_g = glui_bounds->add_rollout_to_panel(PANEL_panel, _d("Bound data"), false);
  if(bound_rollout != NULL)*bound_rollout = PANEL_g;

  PANEL_a = glui_bounds->add_panel_to_panel(PANEL_g, "", GLUI_PANEL_NONE);

  *EDIT_con_min = glui_bounds->add_edittext_to_panel(PANEL_a, "", GLUI_EDITTEXT_FLOAT, minval, VALMIN, FILE_CB);
  if(*setminval == 0){
    (*EDIT_con_min)->disable();
  }
  glui_bounds->add_column_to_panel(PANEL_a, false);

  if(STATIC_con_min_unit != NULL){
    *STATIC_con_min_unit = glui_bounds->add_statictext_to_panel(PANEL_a, "xx");
    glui_bounds->add_column_to_panel(PANEL_a, false);
    (*STATIC_con_min_unit)->set_w(10);
  }

  *RADIO_con_setmin = glui_bounds->add_radiogroup_to_panel(PANEL_a, setminval, SETVALMIN, FILE_CB);
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmin, _d("percentile min"));
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmin, _d("set min"));
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmin, _d("global min"));

  PANEL_b = glui_bounds->add_panel_to_panel(PANEL_g, "", GLUI_PANEL_NONE);

  *EDIT_con_max = glui_bounds->add_edittext_to_panel(PANEL_b, "", GLUI_EDITTEXT_FLOAT, maxval, VALMAX, FILE_CB);
  if(*setminval == 0){
    (*EDIT_con_max)->disable();
  }
  glui_bounds->add_column_to_panel(PANEL_b, false);

  if(STATIC_con_max_unit != NULL){
    *STATIC_con_max_unit = glui_bounds->add_statictext_to_panel(PANEL_b, "yy");
    glui_bounds->add_column_to_panel(PANEL_b, false);
    (*STATIC_con_max_unit)->set_w(10);
  }

  *RADIO_con_setmax = glui_bounds->add_radiogroup_to_panel(PANEL_b, setmaxval, SETVALMAX, FILE_CB);
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmax, _d("percentile max"));
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmax, _d("set max"));
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmax, _d("global max"));

  PANEL_c = glui_bounds->add_panel_to_panel(PANEL_g, "", GLUI_PANEL_NONE);

  if(updatebounds == UPDATE_BOUNDS){
    glui_bounds->add_button_to_panel(PANEL_c, _d("Update"), FILEUPDATE, FILE_CB);
  }
  else if(updatebounds == RELOAD_BOUNDS){
    glui_bounds->add_button_to_panel(PANEL_c, button_title, FILERELOAD, FILE_CB);
  }
  else{
    BUTTON_updatebound = glui_bounds->add_button_to_panel(PANEL_c, _d("Update using cached data"), FILEUPDATEDATA, FILE_CB);
    BUTTON_reloadbound = glui_bounds->add_button_to_panel(PANEL_c, button_title, FILERELOAD, FILE_CB);
  }

  if(EDIT_con_chopmin != NULL&&EDIT_con_chopmax != NULL&&CHECKBOX_con_setchopmin != NULL&&CHECKBOX_con_setchopmax != NULL){
    PANEL_e = glui_bounds->add_rollout_to_panel(PANEL_panel, _d("Truncate data"), false);
    if(chop_rollout != NULL)*chop_rollout = PANEL_e;

    PANEL_f = glui_bounds->add_panel_to_panel(PANEL_e, "", GLUI_PANEL_NONE);

    *EDIT_con_chopmin = glui_bounds->add_edittext_to_panel(PANEL_f, "", GLUI_EDITTEXT_FLOAT, chopminval, CHOPVALMIN, FILE_CB);
    glui_bounds->add_column_to_panel(PANEL_f, false);

    if(STATIC_con_cmin_unit != NULL){
      *STATIC_con_cmin_unit = glui_bounds->add_statictext_to_panel(PANEL_f, "xx");
      (*STATIC_con_cmin_unit)->set_w(10);
      glui_bounds->add_column_to_panel(PANEL_f, false);
    }
    *CHECKBOX_con_setchopmin = glui_bounds->add_checkbox_to_panel(PANEL_f, _d("Below"), setchopminval, SETCHOPMINVAL, FILE_CB);

    PANEL_h = glui_bounds->add_panel_to_panel(PANEL_e, "", GLUI_PANEL_NONE);

    *EDIT_con_chopmax = glui_bounds->add_edittext_to_panel(PANEL_h, "", GLUI_EDITTEXT_FLOAT, chopmaxval, CHOPVALMAX, FILE_CB);
    glui_bounds->add_column_to_panel(PANEL_h, false);

    if(STATIC_con_cmax_unit != NULL){
      *STATIC_con_cmax_unit = glui_bounds->add_statictext_to_panel(PANEL_h, "xx");
      glui_bounds->add_column_to_panel(PANEL_h, false);
      (*STATIC_con_cmax_unit)->set_w(10);
    }
    *CHECKBOX_con_setchopmax = glui_bounds->add_checkbox_to_panel(PANEL_h, _d("Above"), setchopmaxval, SETCHOPMAXVAL, FILE_CB);

    if(truncatebounds == TRUNCATE_BOUNDS){
      glui_bounds->add_button_to_panel(PANEL_e, _d("Update"), CHOPUPDATE, FILE_CB);
    }
  }
}

/* ------------------ GluiBoundsSetup ------------------------ */

extern "C" void GluiBoundsSetup(int main_window){
  int i;
  int nradio;
  int have_part, have_evac;

  update_glui_bounds=0;
  if(glui_bounds!=NULL){
    glui_bounds->close();
    glui_bounds=NULL;
  }
  overwrite_all=0;
  glui_bounds = GLUI_Master.create_glui( "Files/Bounds",0,0,0 );
  glui_bounds->hide();

  PANEL_files = glui_bounds->add_panel("Files", true);

  ROLLOUT_autoload = glui_bounds->add_rollout_to_panel(PANEL_files,_d("Auto load"), false, LOAD_ROLLOUT, FileRolloutCB);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_autoload, LOAD_ROLLOUT);

  glui_bounds->add_checkbox_to_panel(ROLLOUT_autoload, _d("Auto load at startup"),
    &loadfiles_at_startup, STARTUP, BoundBoundCB);
  glui_bounds->add_button_to_panel(ROLLOUT_autoload, _d("Save auto load file list"), SAVE_FILE_LIST, BoundBoundCB);
  glui_bounds->add_button_to_panel(ROLLOUT_autoload, _d("Auto load now"), LOAD_FILES, BoundBoundCB);

  // -------------- Show/Hide Loaded files -------------------

  if(npartinfo > 0 || nsliceinfo > 0 || nvsliceinfo > 0 || nisoinfo > 0 || npatchinfo || nsmoke3dinfo > 0 || nplot3dinfo > 0){
    ROLLOUT_showhide = glui_bounds->add_rollout_to_panel(PANEL_files,"Show/Hide", false, SHOWHIDE_ROLLOUT, FileRolloutCB);
    ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_showhide, SHOWHIDE_ROLLOUT);

    RADIO_showhide = glui_bounds->add_radiogroup_to_panel(ROLLOUT_showhide, &showhide_option);
    glui_bounds->add_radiobutton_to_group(RADIO_showhide, _d("Show"));
    glui_bounds->add_radiobutton_to_group(RADIO_showhide, _d("Show Only"));
    glui_bounds->add_radiobutton_to_group(RADIO_showhide, _d("Hide"));

    glui_bounds->add_column_to_panel(ROLLOUT_showhide, false);

    if(nevac > 0){}
    if(npartinfo > 0 && nevac != npartinfo)BUTTON_PART = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Particle", FILESHOW_particle, FileShowCB);
    if(nevac > 0)BUTTON_EVAC = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Evacuation", FILESHOW_evac, FileShowCB);
    if(nsliceinfo > 0)BUTTON_SLICE = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Slice", FILESHOW_slice, FileShowCB);
    if(nvsliceinfo > 0)BUTTON_VSLICE = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Vector", FILESHOW_vslice, FileShowCB);
    if(nisoinfo > 0)BUTTON_ISO = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Isosurface", FILESHOW_isosurface, FileShowCB);
    if(npatchinfo > 0)BUTTON_BOUNDARY = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Boundary", FILESHOW_boundary, FileShowCB);
    if(nsmoke3dinfo > 0)BUTTON_3DSMOKE = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "3D smoke/fire", FILESHOW_3dsmoke, FileShowCB);
    if(nplot3dinfo > 0)BUTTON_PLOT3D = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Plot3D", FILESHOW_plot3d, FileShowCB);

    UpdateShowHideButtons();
  }


#ifdef pp_COMPRESS
  if(smokezippath != NULL && (npatchinfo > 0 || nsmoke3dinfo > 0 || nsliceinfo > 0)){
    ROLLOUT_compress = glui_bounds->add_rollout_to_panel(PANEL_files,_d("Compress"), false, COMPRESS_ROLLOUT, FileRolloutCB);
    ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_compress, COMPRESS_ROLLOUT);

    CHECKBOX_erase_all = glui_bounds->add_checkbox_to_panel(ROLLOUT_compress, _d("Erase compressed files"),
      &erase_all, ERASE, BoundBoundCB);
    CHECKBOX_overwrite_all = glui_bounds->add_checkbox_to_panel(ROLLOUT_compress, _d("Overwrite compressed files"),
      &overwrite_all, OVERWRITE, BoundBoundCB);
    CHECKBOX_compress_autoloaded = glui_bounds->add_checkbox_to_panel(ROLLOUT_compress, _d("Compress only autoloaded files"),
      &compress_autoloaded, COMPRESS_AUTOLOADED, BoundBoundCB);
    if(nsliceinfo > 0){
      SPINNER_slicezipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _d("Slice frame Skip"), GLUI_SPINNER_INT, &slicezipskip,
        FRAMELOADING, SliceBoundCB);
      SPINNER_slicezipstep->set_int_limits(0, 100);
    }
    if(nisoinfo > 0){
      SPINNER_isozipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _d("Compressed file frame skip"), GLUI_SPINNER_INT, &isozipskip,
        FRAMELOADING, IsoBoundCB);
      SPINNER_isozipstep->set_int_limits(0, 100);
    }
    if(nsmoke3dinfo > 0){
      SPINNER_smoke3dzipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _d("3D smoke frame skip"), GLUI_SPINNER_INT, &smoke3dzipskip,
        FRAMELOADING, Smoke3dBoundCB);
      SPINNER_smoke3dzipstep->set_int_limits(0, 100);
    }
    if(npatchinfo > 0){
      SPINNER_boundzipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _d("Boundary file frame skip"),
        GLUI_SPINNER_INT, &boundzipskip, FRAMELOADING, BoundBoundCB);
      SPINNER_boundzipstep->set_int_limits(0, 100);
    }
    BUTTON_compress = glui_bounds->add_button_to_panel(ROLLOUT_compress, _d("Run smokezip"), COMPRESS_FILES, BoundBoundCB);
  }
#endif

  ROLLOUT_script = glui_bounds->add_rollout_to_panel(PANEL_files,"Scripts", false, SCRIPT_ROLLOUT, FileRolloutCB);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_script, SCRIPT_ROLLOUT);

  PANEL_script1 = glui_bounds->add_panel_to_panel(ROLLOUT_script, _d("Script files"), false);
  PANEL_record = glui_bounds->add_panel_to_panel(PANEL_script1, _d("Record"), true);

  PANEL_script1a = glui_bounds->add_panel_to_panel(PANEL_record, "", false);
  BUTTON_script_start = glui_bounds->add_button_to_panel(PANEL_script1a, _d("Start"), SCRIPT_START, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script1a, false);
  BUTTON_script_stop = glui_bounds->add_button_to_panel(PANEL_script1a, _d("Stop"), SCRIPT_STOP, ScriptCB);
  BUTTON_script_stop->disable();

  CHECKBOX_defer = glui_bounds->add_checkbox_to_panel(PANEL_record, _d("Turn off file loading while recording"), &defer_file_loading,
    SCRIPT_FILE_LOADING, ScriptCB);

  PANEL_run = glui_bounds->add_panel_to_panel(PANEL_script1, _d("Run"), true);
  PANEL_script1b = glui_bounds->add_panel_to_panel(PANEL_run, "", false);
  BUTTON_script_runscript = glui_bounds->add_button_to_panel(PANEL_script1b, _d("Run script"), SCRIPT_RUNSCRIPT, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script1b, false);
  CHECKBOX_script_step = glui_bounds->add_checkbox_to_panel(PANEL_run, _d("Step through script"), &script_step, SCRIPT_STEP, ScriptCB);
  BUTTON_step = glui_bounds->add_button_to_panel(PANEL_run, _d("Next"), SCRIPT_STEP_NOW, ScriptCB);
  UpdateScriptStep();
  glui_bounds->add_button_to_panel(PANEL_run, _d("Cancel script"), SCRIPT_CANCEL_NOW, ScriptCB);

  LIST_scriptlist = glui_bounds->add_listbox_to_panel(PANEL_script1b, _d("Select:"), &script_index, SCRIPT_LIST, ScriptCB);
  {
    scriptfiledata *scriptfile;

    for(scriptfile = first_scriptfile.next; scriptfile->next != NULL; scriptfile = scriptfile->next){
      char *file;
      int len;

      file = scriptfile->file;
      if(file == NULL)continue;
      if(FILE_EXISTS(file) == NO)continue;
      len = strlen(file);
      if(len <= 0)continue;

      LIST_scriptlist->add_item(scriptfile->id, file);
    }
    ScriptCB(SCRIPT_LIST);
  }

  ROLLOUT_config = glui_bounds->add_rollout_to_panel(PANEL_files, "Config", false, CONFIG_ROLLOUT, FileRolloutCB);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_config, CONFIG_ROLLOUT);

  PANEL_script2a = glui_bounds->add_panel_to_panel(ROLLOUT_config, "", false);
  EDIT_ini = glui_bounds->add_edittext_to_panel(PANEL_script2a, "suffix:", GLUI_EDITTEXT_TEXT, script_inifile_suffix, SCRIPT_EDIT_INI, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script2a, false);
  BUTTON_script_setsuffix = glui_bounds->add_button_to_panel(PANEL_script2a, _d("Set"), SCRIPT_SETSUFFIX, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script2a, false);
  BUTTON_script_saveini = glui_bounds->add_button_to_panel(PANEL_script2a, _d("Save:"), SCRIPT_SAVEINI, ScriptCB);
  ScriptCB(SCRIPT_EDIT_INI);

  PANEL_script2b = glui_bounds->add_panel_to_panel(ROLLOUT_config, "", false);
  ini_index = -2;
  LIST_ini_list = glui_bounds->add_listbox_to_panel(PANEL_script2b, _d("Select:"), &ini_index);
  {
    inifiledata *inifile;

    for(inifile = first_inifile.next; inifile->next != NULL; inifile = inifile->next){
      if(inifile->file != NULL&&FILE_EXISTS(inifile->file) == YES){
        if(ini_index == -2)ini_index = inifile->id;
        LIST_ini_list->add_item(inifile->id, inifile->file);
      }
    }
  }
  glui_bounds->add_column_to_panel(PANEL_script2b, false);
  BUTTON_ini_load = glui_bounds->add_button_to_panel(PANEL_script2b, _d("Load"), SCRIPT_LOADINI, ScriptCB);

  PANEL_script3 = glui_bounds->add_panel_to_panel(ROLLOUT_script, _d("Render"), true);
  EDIT_renderdir = glui_bounds->add_edittext_to_panel(PANEL_script3, _d("directory:"),
    GLUI_EDITTEXT_TEXT, script_renderdir, SCRIPT_RENDER_DIR, ScriptCB);
  EDIT_renderdir->set_w(260);
  PANEL_script1c = glui_bounds->add_panel_to_panel(PANEL_script3, "", false);
  BUTTON_script_render = glui_bounds->add_button_to_panel(PANEL_script1c, _d("Render"), SCRIPT_RENDER, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script1c, false);
  EDIT_rendersuffix = glui_bounds->add_edittext_to_panel(PANEL_script1c, _d("suffix:"),
    GLUI_EDITTEXT_TEXT, script_renderfilesuffix, SCRIPT_RENDER_SUFFIX, ScriptCB);
  EDIT_rendersuffix->set_w(130);
  ScriptCB(SCRIPT_RENDER_SUFFIX);


  PANEL_bounds = glui_bounds->add_panel("Bounds",true);
  ROLLOUT_filebounds = glui_bounds->add_rollout_to_panel(PANEL_bounds,"Data", false, FILEBOUNDS_ROLLOUT, FileRolloutCB);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_filebounds, FILEBOUNDS_ROLLOUT);

  /*  zone (cfast) */

  if(nzoneinfo>0){
    ROLLOUT_zone_bound = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"Upper layer temperature",false,ZONE_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_zone_bound, ZONE_ROLLOUT);

    PANEL_zone_a = glui_bounds->add_panel_to_panel(ROLLOUT_zone_bound,"",GLUI_PANEL_NONE);

    EDIT_zone_min = glui_bounds->add_edittext_to_panel(PANEL_zone_a,"",GLUI_EDITTEXT_FLOAT,&zonemin,ZONEVALMIN,SliceBoundCB);
    if(setzonemin==0){
      EDIT_zone_min->disable();
    }
    glui_bounds->add_column_to_panel(PANEL_zone_a,false);

    RADIO_zone_setmin = glui_bounds->add_radiogroup_to_panel(PANEL_zone_a,&setzonemin,SETZONEVALMIN,SliceBoundCB);
    RADIOBUTTON_zone_permin=glui_bounds->add_radiobutton_to_group(RADIO_zone_setmin,_d("percentile min"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmin,_d("set min"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmin,_d("global min"));

    PANEL_zone_b = glui_bounds->add_panel_to_panel(ROLLOUT_zone_bound,"",GLUI_PANEL_NONE);

    EDIT_zone_max = glui_bounds->add_edittext_to_panel(PANEL_zone_b,"",GLUI_EDITTEXT_FLOAT,&zonemax,ZONEVALMAX,SliceBoundCB);
    if(setzonemax==0){
      EDIT_zone_max->disable();
    }
    glui_bounds->add_column_to_panel(PANEL_zone_b,false);

    RADIO_zone_setmax = glui_bounds->add_radiogroup_to_panel(PANEL_zone_b,&setzonemax,SETZONEVALMAX,SliceBoundCB);
    RADIOBUTTON_zone_permax=glui_bounds->add_radiobutton_to_group(RADIO_zone_setmax,_d("percentile max"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmax,_d("set max"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmax,_d("global max"));

    RADIOBUTTON_zone_permin->disable();
    RADIOBUTTON_zone_permax->disable();
    SliceBoundCB(SETZONEVALMIN);
    SliceBoundCB(SETZONEVALMAX);
  }

  /*  3d smoke   */

  if(nsmoke3dinfo>0||nvolrenderinfo>0){
    ROLLOUT_smoke3d = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"3D smoke",false,SMOKE3D_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_smoke3d, SMOKE3D_ROLLOUT);
  }

  /*  Boundary File Bounds   */

  if(npatchinfo>0){
    glui_active=1;
    ROLLOUT_bound = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"Boundary",false,BOUNDARY_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_bound, BOUNDARY_ROLLOUT);

    RADIO_bf = glui_bounds->add_radiogroup_to_panel(ROLLOUT_bound,&list_patch_index,FILETYPEINDEX,BoundBoundCB);
    nradio=0;
    for(i=0;i<npatchinfo;i++){
      patchdata *patchi;

      patchi = patchinfo + i;
      if(patchi->firstshort==1)nradio++;
    }
    CHECKBOX_cache_boundarydata=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound,_d("Cache boundary data"),&cache_boundarydata,CACHE_BOUNDARYDATA,BoundBoundCB);
    CHECKBOX_showpatch_both=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound,_d("Display exterior data"),&showpatch_both,SHOWPATCH_BOTH,BoundBoundCB);
    ROLLOUT_outputpatchdata = glui_bounds->add_rollout_to_panel(ROLLOUT_bound,"Ouput data",false);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_outputpatchdata,_d("Output data to file"),&output_patchdata);

    PANEL_outputpatchdata = glui_bounds->add_panel_to_panel(ROLLOUT_outputpatchdata,"",GLUI_PANEL_NONE);

    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"tmin",GLUI_SPINNER_FLOAT,&patchout_tmin);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"xmin",GLUI_SPINNER_FLOAT,&patchout_xmin);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"ymin",GLUI_SPINNER_FLOAT,&patchout_ymin);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"zmin",GLUI_SPINNER_FLOAT,&patchout_zmin);

    glui_bounds->add_column_to_panel(PANEL_outputpatchdata,false);

    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"tmax",GLUI_SPINNER_FLOAT,&patchout_tmax);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"xmax",GLUI_SPINNER_FLOAT,&patchout_xmax);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"ymax",GLUI_SPINNER_FLOAT,&patchout_ymax);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"zmax",GLUI_SPINNER_FLOAT,&patchout_zmax);


    if(nradio>1){
      for(i=0;i<npatchinfo;i++){
        patchdata *patchi;

        patchi = patchinfo + i;
        if(patchi->firstshort==1)glui_bounds->add_radiobutton_to_group(RADIO_bf,patchi->label.shortlabel);
      }
      if(activate_threshold==1){
        glui_bounds->add_separator_to_panel(ROLLOUT_bound);
        CHECKBOX_showchar=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound,_d("Show temp threshold"),&vis_threshold,SHOWCHAR,BoundBoundCB);
        CHECKBOX_showonlychar=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound,_d("Show only temp threshold"),&vis_onlythreshold,SHOWCHAR,BoundBoundCB);
        {
          char label[256];

          strcpy(label,"Temperature threshold (");
          strcat(label,degC);
          strcat(label,") ");
          glui_bounds->add_spinner_to_panel(ROLLOUT_bound,label,GLUI_SPINNER_FLOAT,&temp_threshold);
        }
        BoundBoundCB(SHOWCHAR);
      }
#ifdef pp_FSEEK
      CHECKBOX_boundary_load_incremental=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound, _d("incremental data loading"), &load_incremental, BOUNDARY_LOAD_INCREMENTAL, LoadIncrementalCB);
      LoadIncrementalCB(BOUNDARY_LOAD_INCREMENTAL);
#endif
      glui_bounds->add_column_to_panel(ROLLOUT_bound,false);
    }
    else{
      if(activate_threshold==1){
        CHECKBOX_showchar=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound,_d("Show temp threshold"),&vis_threshold,SHOWCHAR,BoundBoundCB);
        CHECKBOX_showonlychar=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound,_d("Show only threshold"),&vis_onlythreshold,SHOWCHAR,BoundBoundCB);
        {
          char label[256];

          strcpy(label,"Temperature (");
          strcat(label,degC);
          strcat(label,") ");
          glui_bounds->add_spinner_to_panel(ROLLOUT_bound,label,GLUI_SPINNER_FLOAT,&temp_threshold);
        }
        BoundBoundCB(SHOWCHAR);
      }
    }

    BoundMenu(&ROLLOUT_boundary,NULL,ROLLOUT_bound,"Reload Boundary File(s)",
      &EDIT_patch_min,&EDIT_patch_max,&RADIO_patch_setmin,&RADIO_patch_setmax,
      &CHECKBOX_patch_setchopmin, &CHECKBOX_patch_setchopmax,
      &EDIT_patch_chopmin, &EDIT_patch_chopmax,
      &STATIC_bound_min_unit,&STATIC_bound_max_unit,
      &STATIC_bound_cmin_unit,&STATIC_bound_cmax_unit,
      &BUTTON_updatebound, &BUTTON_reloadbound,
      &setpatchmin,&setpatchmax,&patchmin,&patchmax,
      &setpatchchopmin, &setpatchchopmax,
      &patchchopmin, &patchchopmax,
      UPDATERELOAD_BOUNDS,DONT_TRUNCATE_BOUNDS,
      BoundBoundCB);
    UpdateBoundaryListIndex2(patchinfo->label.shortlabel);
    UpdateHideBoundarySurface();
    BoundBoundCB(CACHE_BOUNDARYDATA);
  }

  /*  Iso File Load Bounds   */

  if(nisoinfo>0){
    ROLLOUT_iso = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds, "Isosurface", false, ISO_ROLLOUT, BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_iso, ISO_ROLLOUT);

    ROLLOUT_iso_settings = glui_bounds->add_rollout_to_panel(ROLLOUT_iso, "Settings", true, ISO_ROLLOUT_SETTINGS, IsoRolloutCB);
    ADDPROCINFO(isoprocinfo, nisoprocinfo, ROLLOUT_iso_settings, ISO_ROLLOUT_SETTINGS);

    SPINNER_isopointsize = glui_bounds->add_spinner_to_panel(ROLLOUT_iso_settings, _d("Point size"), GLUI_SPINNER_FLOAT, &isopointsize);
    SPINNER_isopointsize->set_float_limits(1.0, 10.0);

    SPINNER_isolinewidth = glui_bounds->add_spinner_to_panel(ROLLOUT_iso_settings, _d("Line width"), GLUI_SPINNER_FLOAT, &isolinewidth);
    SPINNER_isolinewidth->set_float_limits(1.0, 10.0);

    visAIso = show_iso_solid*1+show_iso_outline*2+show_iso_verts*4;
    CHECKBOX_show_iso_solid = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _d("Solid"), &show_iso_solid, ISO_SURFACE, IsoBoundCB);
    CHECKBOX_show_iso_outline = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _d("Outline"), &show_iso_outline, ISO_OUTLINE, IsoBoundCB);
    CHECKBOX_show_iso_verts = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _d("Points"), &show_iso_verts, ISO_POINTS, IsoBoundCB);

#ifdef pp_BETA
    CHECKBOX_sort2 = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _d("Sort transparent surfaces:"), &sort_iso_triangles, SORT_SURFACES, SliceBoundCB);
#endif
    CHECKBOX_smooth2 = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _d("Smooth isosurfaces"), &smooth_iso_normal, SMOOTH_SURFACES, SliceBoundCB);

    ROLLOUT_iso_color = glui_bounds->add_rollout_to_panel(ROLLOUT_iso, "Color/transparency", false, ISO_ROLLOUT_COLOR, IsoRolloutCB);
    ADDPROCINFO(isoprocinfo, nisoprocinfo, ROLLOUT_iso_color, ISO_ROLLOUT_COLOR);

    CHECKBOX_transparentflag2 = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_color, _d("Use transparency"), &use_transparency_data, DATA_transparent, SliceBoundCB);

    PANEL_iso_alllevels = glui_bounds->add_panel_to_panel(ROLLOUT_iso_color, "All levels", true);

    SPINNER_iso_transparency = glui_bounds->add_spinner_to_panel(PANEL_iso_alllevels, "alpha", GLUI_SPINNER_INT, &glui_iso_transparency, ISO_TRANSPARENCY, IsoBoundCB);
    BUTTON_updatebound = glui_bounds->add_button_to_panel(PANEL_iso_alllevels, _d("Apply"), GLOBAL_ALPHA, IsoBoundCB);

    PANEL_iso_eachlevel = glui_bounds->add_panel_to_panel(ROLLOUT_iso_color, "Each level", true);
    SPINNER_iso_level = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "level:", GLUI_SPINNER_INT, &glui_iso_level, ISO_LEVEL, IsoBoundCB);
    SPINNER_iso_level->set_int_limits(1, MAX_ISO_COLORS);
    LIST_colortable = glui_bounds->add_listbox_to_panel(PANEL_iso_eachlevel, _d("Color:"), &i_colortable_list, COLORTABLE_LIST, IsoBoundCB);
    SPINNER_iso_colors[0] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "red:", GLUI_SPINNER_INT, glui_iso_colors+0, ISO_COLORS, IsoBoundCB);
    SPINNER_iso_colors[1] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "green:", GLUI_SPINNER_INT, glui_iso_colors+1, ISO_COLORS, IsoBoundCB);
    SPINNER_iso_colors[2] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "blue:", GLUI_SPINNER_INT, glui_iso_colors+2, ISO_COLORS, IsoBoundCB);
    SPINNER_iso_colors[3] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "alpha:", GLUI_SPINNER_INT, glui_iso_colors+3, ISO_COLORS, IsoBoundCB);

    UpdateColorTableList(-1);

    SPINNER_iso_colors[0]->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
    SPINNER_iso_colors[1]->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
    SPINNER_iso_colors[2]->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
    SPINNER_iso_colors[3]->set_int_limits(1, 255, GLUI_LIMIT_CLAMP);
    IsoBoundCB(ISO_LEVEL);
    IsoBoundCB(ISO_COLORS);
  }

  /* Particle File Bounds  */

  have_part = 0;
  have_evac = 0;
  if(npartinfo > 0 && nevac != npartinfo)have_part = 1;
  if(nevac > 0)have_evac = 1;
  if(have_part==1||have_evac==1){
  char label[100];

  strcpy(label, "");
  if(have_part == 1)strcat(label, "Particle");
  if(have_part == 1 && have_evac == 1)strcat(label, "/");
  if(have_evac == 1)strcat(label, "Evac");

    glui_active=1;
    ROLLOUT_part = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,label,false,PART_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_part, PART_ROLLOUT);

    if(npart5prop>0){
      ipart5prop=0;
      ipart5prop_old=0;
      RADIO_part5 = glui_bounds->add_radiogroup_to_panel(ROLLOUT_part,&ipart5prop,FILETYPEINDEX,PartBoundCB);

      for(i=0;i<npart5prop;i++){
        partpropdata *partpropi;

        partpropi = part5propinfo + i;
        glui_bounds->add_radiobutton_to_group(RADIO_part5,partpropi->label->shortlabel);
      }

      glui_bounds->add_column_to_panel(ROLLOUT_part,false);

      {
        partpropdata *propi;

        propi = part5propinfo;
        setpartmin=propi->setvalmin;
        setpartmax=propi->setvalmax;
        setpartchopmin=propi->setchopmin;
        setpartchopmax=propi->setchopmax;
      }

      PartBoundCB(FILETYPEINDEX);
      PartBoundCB(SETVALMIN);
      PartBoundCB(SETVALMAX);
    }

    {
      char boundmenulabel[100];

      strcpy(boundmenulabel, "Reload ");
      strcat(boundmenulabel, label);
      strcat(boundmenulabel, " File");
      if(npartinfo > 1)strcat(boundmenulabel, "s");
      BoundMenu(&ROLLOUT_part_bound,&ROLLOUT_part_chop,ROLLOUT_part,boundmenulabel,
        &EDIT_part_min,&EDIT_part_max,&RADIO_part_setmin,&RADIO_part_setmax,
        &CHECKBOX_part_setchopmin, &CHECKBOX_part_setchopmax,
        &EDIT_part_chopmin, &EDIT_part_chopmax,
        &STATIC_part_min_unit,&STATIC_part_max_unit,
        NULL,NULL,
        NULL,NULL,
        &setpartmin,&setpartmax,&partmin,&partmax,
        &setpartchopmin,&setpartchopmax,&partchopmin,&partchopmax,
        RELOAD_BOUNDS,DONT_TRUNCATE_BOUNDS,
        PartBoundCB);
      PartBoundCB(FILETYPEINDEX);
      SPINNER_partpointsize=glui_bounds->add_spinner_to_panel(ROLLOUT_part,_d("Particle size"),GLUI_SPINNER_FLOAT,&partpointsize);
      SPINNER_partpointsize->set_float_limits(1.0,100.0);
      SPINNER_streaklinewidth=glui_bounds->add_spinner_to_panel(ROLLOUT_part,_d("Streak line width"),GLUI_SPINNER_FLOAT,&streaklinewidth);
      SPINNER_streaklinewidth->set_float_limits(1.0,100.0);

      SPINNER_partstreaklength=glui_bounds->add_spinner_to_panel(ROLLOUT_part,_d("Streak length (s)"),GLUI_SPINNER_FLOAT,&float_streak5value,STREAKLENGTH,PartBoundCB);
      SPINNER_partstreaklength->set_float_limits(0.0,tmax_part);

      CHECKBOX_showtracer=glui_bounds->add_checkbox_to_panel(ROLLOUT_part,_d("Always show tracers"),&show_tracers_always,TRACERS,PartBoundCB);
    }
  }

  if(have_evac==1){
    glui_active=1;

    glui_bounds->add_checkbox_to_panel(ROLLOUT_part,_d("Select avatar"),&select_avatar);
    CHECKBOX_show_evac_slices=glui_bounds->add_checkbox_to_panel(ROLLOUT_part,"Show slice menus",&show_evac_slices,SHOW_EVAC_SLICES,SliceBoundCB);
    PANEL_evac_direction=glui_bounds->add_panel_to_panel(ROLLOUT_part,_d("Direction vectors"));
    CHECKBOX_constant_coloring=glui_bounds->add_checkbox_to_panel(PANEL_evac_direction,_d("Constant coloring"),&constant_evac_coloring,SHOW_EVAC_SLICES,SliceBoundCB);
    CHECKBOX_data_coloring=glui_bounds->add_checkbox_to_panel(PANEL_evac_direction,_d("Data coloring"),&data_evac_coloring,DATA_EVAC_COLORING,SliceBoundCB);
    CHECKBOX_show_evac_color=glui_bounds->add_checkbox_to_panel(PANEL_evac_direction,_d("Show colorbar (when data coloring)"),&show_evac_colorbar,SHOW_EVAC_SLICES,SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_part,_d("View from selected Avatar"),&view_from_selected_avatar);
  }

  /* Plot3D file bounds */

  if(nplot3dinfo>0){
    glui_active=1;
    ROLLOUT_plot3d = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"Plot3D",false,PLOT3D_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_plot3d, PLOT3D_ROLLOUT);

    RADIO_p3 = glui_bounds->add_radiogroup_to_panel(ROLLOUT_plot3d,&list_p3_index,FILETYPEINDEX,Plot3DBoundCB);
    for(i=0;i<mxplot3dvars;i++){
      glui_bounds->add_radiobutton_to_group(RADIO_p3,plot3dinfo[0].label[i].shortlabel);
    }
    CHECKBOX_cache_qdata=glui_bounds->add_checkbox_to_panel(ROLLOUT_plot3d,_d("Cache Plot3D data"),&cache_qdata,UNLOAD_QDATA,Plot3DBoundCB);

    PANEL_pan3 = glui_bounds->add_panel_to_panel(ROLLOUT_plot3d,"",GLUI_PANEL_NONE);
    ROLLOUT_vector = glui_bounds->add_rollout_to_panel(PANEL_pan3,_d("Vector"),false,VECTOR_ROLLOUT, Plot3dRolloutCB);
    ADDPROCINFO(plot3dprocinfo, nplot3dprocinfo, ROLLOUT_vector, VECTOR_ROLLOUT);

    glui_bounds->add_checkbox_to_panel(ROLLOUT_vector,_d("Show vectors"),&visVector,UPDATEPLOT,Plot3DBoundCB);
    SPINNER_plot3d_vectorpointsize=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_d("Point size"),GLUI_SPINNER_FLOAT,&vectorpointsize,UPDATE_VECTOR,Plot3DBoundCB);
    SPINNER_plot3d_vectorpointsize->set_float_limits(1.0,10.0);
    SPINNER_plot3d_vectorlinewidth=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_d("Vector width"),GLUI_SPINNER_FLOAT,&vectorlinewidth,UPDATE_VECTOR,Plot3DBoundCB);
    SPINNER_plot3d_vectorlinewidth->set_float_limits(1.0,10.0);
    SPINNER_plot3d_vectorlinelength=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_d("Vector length"),GLUI_SPINNER_FLOAT,&vecfactor,UPDATE_VECTOR,Plot3DBoundCB);
    SPINNER_plot3d_vectorlinelength->set_float_limits(0.0,20.0);
    SPINNER_plot3dvectorskip=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_d("Vector skip"),GLUI_SPINNER_INT,&vectorskip,PLOT3D_VECTORSKIP,Plot3DBoundCB);
    SPINNER_plot3dvectorskip->set_int_limits(1,4);

    ROLLOUT_isosurface = glui_bounds->add_rollout_to_panel(ROLLOUT_plot3d,"Isosurface",false,ISOSURFACE_ROLLOUT, Plot3dRolloutCB);
    ADDPROCINFO(plot3dprocinfo, nplot3dprocinfo, ROLLOUT_isosurface, ISOSURFACE_ROLLOUT);

    PANEL_pan1 = glui_bounds->add_panel_to_panel(ROLLOUT_isosurface,"",GLUI_PANEL_NONE);

    glui_bounds->add_checkbox_to_panel(PANEL_pan1,"Show isosurface",&visiso,PLOTISO,Plot3DBoundCB);
    SPINNER_plot3dpointsize=glui_bounds->add_spinner_to_panel(PANEL_pan1,_d("Point size"),GLUI_SPINNER_FLOAT,
      &plot3dpointsize);
    SPINNER_plot3dpointsize->set_float_limits(1.0,10.0);

    SPINNER_plot3dlinewidth=glui_bounds->add_spinner_to_panel(PANEL_pan1,_d("Line width"),GLUI_SPINNER_FLOAT,
      &plot3dlinewidth);
    SPINNER_plot3dlinewidth->set_float_limits(1.0,10.0);
//    glui_bounds->add_column_to_panel(ROLLOUT_isosurface);
    PANEL_pan2 = glui_bounds->add_panel_to_panel(ROLLOUT_isosurface,"",GLUI_PANEL_NONE);
    RADIO_plot3d_isotype=glui_bounds->add_radiogroup_to_panel(PANEL_pan2,&p3dsurfacetype,PLOTISOTYPE,Plot3DBoundCB);
    RADIOBUTTON_plot3d_iso_hidden=glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_d("Hidden"));
    glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_d("Solid"));
    glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_d("Outline"));
    glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_d("Points"));
    RADIOBUTTON_plot3d_iso_hidden->disable();

    p3min_temp=p3min[0];
    p3max_temp=p3max[0];
    p3chopmin_temp=p3chopmin[0];
    p3chopmax_temp=p3chopmax[0];
    glui_bounds->add_column_to_panel(ROLLOUT_plot3d,false);
    BoundMenu(NULL,NULL,ROLLOUT_plot3d,"Reload Plot3D file(s)",
      &EDIT_p3_min,&EDIT_p3_max,&RADIO_p3_setmin,&RADIO_p3_setmax,
      &CHECKBOX_p3_setchopmin, &CHECKBOX_p3_setchopmax,
      &EDIT_p3_chopmin, &EDIT_p3_chopmax,
      &STATIC_plot3d_min_unit,&STATIC_plot3d_max_unit,
      &STATIC_plot3d_cmin_unit,&STATIC_plot3d_cmax_unit,
      NULL,NULL,
      &setp3min_temp,&setp3max_temp,&p3min_temp,&p3max_temp,
      &setp3chopmin_temp, &setp3chopmax_temp,&p3chopmin_temp,&p3chopmax_temp,
      RELOAD_BOUNDS,TRUNCATE_BOUNDS,
      Plot3DBoundCB);
    Plot3DBoundCB(FILETYPEINDEX);
    Plot3DBoundCB(UNLOAD_QDATA);
  }

  /*  Slice File Bounds   */

  if(nsliceinfo>0){
    int index;

    glui_active=1;
    ROLLOUT_slice = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"Slice",false,SLICE_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_slice, SLICE_ROLLOUT);

    RADIO_slice = glui_bounds->add_radiogroup_to_panel(ROLLOUT_slice,&list_slice_index,FILETYPEINDEX,SliceBoundCB);

    index=0;
    for(i=0;i<nsliceinfo;i++){
      if(sliceinfo[i].firstshort==1){
        GLUI_RadioButton *RADIOBUTTON_slicetype;

        RADIOBUTTON_slicetype=glui_bounds->add_radiobutton_to_group(RADIO_slice,sliceinfo[i].label.shortlabel);
        if(strcmp(sliceinfo[i].label.shortlabel,_d("Fire line"))==0){
          RADIOBUTTON_slicetype->disable();
          fire_line_index=index;
        }
        index++;
      }
    }

    glui_bounds->add_column_to_panel(ROLLOUT_slice,false);

    BoundMenu(&ROLLOUT_slice_bound,&ROLLOUT_slice_chop,ROLLOUT_slice,"Reload Slice File(s)",
      &EDIT_slice_min,&EDIT_slice_max,&RADIO_slice_setmin,&RADIO_slice_setmax,
      &CHECKBOX_slice_setchopmin, &CHECKBOX_slice_setchopmax,
      &EDIT_slice_chopmin, &EDIT_slice_chopmax,
      &STATIC_slice_min_unit,&STATIC_slice_max_unit,
      &STATIC_slice_cmin_unit,&STATIC_slice_cmax_unit,
      NULL,NULL,
      &setslicemin,&setslicemax,&slicemin,&slicemax,
      &setslicechopmin, &setslicechopmax,
      &slicechopmin, &slicechopmax,
      UPDATE_BOUNDS,DONT_TRUNCATE_BOUNDS,
      SliceBoundCB);

    ROLLOUT_slice_histogram = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _d("Histogram"), false, SLICE_HISTOGRAM_ROLLOUT, SliceRolloutCB);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_histogram, SLICE_HISTOGRAM_ROLLOUT);

    RADIO_histogram_static = glui_bounds->add_radiogroup_to_panel(ROLLOUT_slice_histogram,&histogram_static);
    glui_bounds->add_radiobutton_to_group(RADIO_histogram_static,"each time");
    glui_bounds->add_radiobutton_to_group(RADIO_histogram_static,"all times");
    SPINNER_histogram_width_factor=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_histogram, _d("val at left"), GLUI_SPINNER_FLOAT,&histogram_width_factor);
    SPINNER_histogram_width_factor->set_float_limits(1.0,100.0);
    SPINNER_histogram_nbuckets=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_histogram, _d("bins"), GLUI_SPINNER_INT,&histogram_nbuckets,UPDATE_HISTOGRAM,SliceBoundCB);
    SPINNER_histogram_nbuckets->set_int_limits(3,255);
    CHECKBOX_histogram_show_numbers = glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_histogram, _d("percentages"), &histogram_show_numbers, INIT_HISTOGRAM, SliceBoundCB);
    CHECKBOX_histogram_show_graph=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_histogram, _d("graph"), &histogram_show_graph, INIT_HISTOGRAM, SliceBoundCB);
    CHECKBOX_histogram_show_outline=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_histogram, _d("outline"), &histogram_show_outline);

    ROLLOUT_slice_average=glui_bounds->add_rollout_to_panel(ROLLOUT_slice,_d("Average data"),false,SLICE_AVERAGE_ROLLOUT,SliceRolloutCB);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_average, SLICE_AVERAGE_ROLLOUT);

    CHECKBOX_average_slice=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_average,_d("Average slice data"),&slice_average_flag);
    SPINNER_sliceaverage=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_average,_d("Time interval"),GLUI_SPINNER_FLOAT,&slice_average_interval);
    {
      float tttmax=120.0;

      if(view_tstop>tttmax)tttmax=view_tstop;
      SPINNER_sliceaverage->set_float_limits(0.0,tttmax);
    }
    glui_bounds->add_button_to_panel(ROLLOUT_slice_average,"Reload",ALLFILERELOAD,SliceBoundCB);

    ROLLOUT_slice_vector = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _d("Vector"), false, SLICE_VECTOR_ROLLOUT, SliceRolloutCB);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_vector, SLICE_VECTOR_ROLLOUT);

    SPINNER_vectorpointsize = glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector, _d("Point size"), GLUI_SPINNER_FLOAT,
      &vectorpointsize,UPDATE_VECTOR,SliceBoundCB);
    SPINNER_vectorpointsize->set_float_limits(1.0,10.0);
    SPINNER_vectorlinewidth=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector,_d("Vector width"),GLUI_SPINNER_FLOAT,&vectorlinewidth,UPDATE_VECTOR,SliceBoundCB);
    SPINNER_vectorlinewidth->set_float_limits(1.0,10.0);
    SPINNER_vectorlinelength=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector,_d("Vector length"),GLUI_SPINNER_FLOAT,&vecfactor,UPDATE_VECTOR,SliceBoundCB);
    SPINNER_vectorlinelength->set_float_limits(0.0,20.0);
    SPINNER_slicevectorskip=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector,_d("Vector skip"),GLUI_SPINNER_INT,&vectorskip,SLICE_VECTORSKIP,SliceBoundCB);
    SPINNER_slicevectorskip->set_int_limits(1,4);
    CHECKBOX_color_vector_black = glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_vector, _d("Color black"), &color_vector_black);

    CHECKBOX_show_node_slices_and_vectors=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_vector,_d("Show vectors and node centered slices"),&show_node_slices_and_vectors);
    CHECKBOX_show_node_slices_and_vectors=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_vector,_d("Show vectors and cell centered slices"),&show_cell_slices_and_vectors);
    ROLLOUT_line_contour = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _d("Line Contours"), false, LINE_CONTOUR_ROLLOUT, SliceRolloutCB);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_line_contour, LINE_CONTOUR_ROLLOUT);

    slice_line_contour_min = 0.0;
    slice_line_contour_max=1.0;
    SPINNER_line_contour_min=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_d("Min"),GLUI_SPINNER_FLOAT,
      &slice_line_contour_min,LINE_CONTOUR_VALUE,SliceBoundCB);
    SPINNER_line_contour_max=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_d("Max"),GLUI_SPINNER_FLOAT,
      &slice_line_contour_max,LINE_CONTOUR_VALUE,SliceBoundCB);
    slice_line_contour_num=1;
    SPINNER_line_contour_num=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_d("Number of contours"),GLUI_SPINNER_INT,
      &slice_line_contour_num,LINE_CONTOUR_VALUE,SliceBoundCB);
    SPINNER_line_contour_width=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_d("contour width"),GLUI_SPINNER_FLOAT,&slice_line_contour_width);
    SPINNER_line_contour_width->set_float_limits(1.0,10.0);
      RADIO_contour_type = glui_bounds->add_radiogroup_to_panel(ROLLOUT_line_contour,&slice_contour_type);
    glui_bounds->add_radiobutton_to_group(RADIO_contour_type,"line");
#ifdef _DEBUG
    glui_bounds->add_radiobutton_to_group(RADIO_contour_type,"stepped");
#endif

    BUTTON_update_line_contour=glui_bounds->add_button_to_panel(ROLLOUT_line_contour,_d("Update contours"),UPDATE_LINE_CONTOUR_VALUE,SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_line_contour,_d("Show contours"),&vis_slice_contours);

    if(n_embedded_meshes>0){
      CHECKBOX_skip_subslice=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice,_d("Skip coarse sub-slice"),&skip_slice_in_embedded_mesh);
    }
    if(nslicedups > 0){
      ROLLOUT_slicedups = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _d("Duplicates"), false, SLICE_DUP_ROLLOUT, SliceRolloutCB);
      ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slicedups, SLICE_DUP_ROLLOUT);

      PANEL_slicedup = glui_bounds->add_panel_to_panel(ROLLOUT_slicedups,"slices",true);
      RADIO_slicedup = glui_bounds->add_radiogroup_to_panel(PANEL_slicedup, &slicedup_option,UPDATE_SLICEDUPS,SliceBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_slicedup, _d("Keep all"));
      glui_bounds->add_radiobutton_to_group(RADIO_slicedup, _d("Keep fine"));
      glui_bounds->add_radiobutton_to_group(RADIO_slicedup, _d("Keep coarse"));

      PANEL_vectorslicedup = glui_bounds->add_panel_to_panel(ROLLOUT_slicedups,"vector slices",true);
      RADIO_vectorslicedup = glui_bounds->add_radiogroup_to_panel(PANEL_vectorslicedup, &vectorslicedup_option, UPDATE_SLICEDUPS, SliceBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_vectorslicedup, _d("Keep all"));
      glui_bounds->add_radiobutton_to_group(RADIO_vectorslicedup, _d("Keep fine"));
      glui_bounds->add_radiobutton_to_group(RADIO_vectorslicedup, _d("Keep coarse"));
    }

    SPINNER_transparent_level = glui_bounds->add_spinner_to_panel(ROLLOUT_slice, _d("Transparent level"), GLUI_SPINNER_FLOAT, &transparent_level, TRANSPARENTLEVEL, SliceBoundCB);
    SPINNER_transparent_level->set_float_limits(0.0, 1.0);

    PANEL_sliceshow = glui_bounds->add_panel_to_panel(ROLLOUT_slice, "show slice", true);
    RADIO_show_slice_in_obst = glui_bounds->add_radiogroup_to_panel(PANEL_sliceshow, &show_slice_in_obst, SLICE_IN_OBST, SliceBoundCB);
    glui_bounds->add_radiobutton_to_group(RADIO_show_slice_in_obst, _d("gas"));
    glui_bounds->add_radiobutton_to_group(RADIO_show_slice_in_obst, _d("gas and solid"));
    glui_bounds->add_radiobutton_to_group(RADIO_show_slice_in_obst, _d("solid"));

    if(nfedinfo>0){
      glui_bounds->add_checkbox_to_panel(ROLLOUT_slice,"Regenerate FED data",&regenerate_fed);
    }
    CHECKBOX_research_mode=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice,_d("Research display mode"),&research_mode,RESEARCH_MODE,SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice,_d("Output data to file"),&output_slicedata);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice, _d("show all 3d slices"), &showall_3dslices);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice, _d("max blending"), &slices3d_max_blending);
#ifdef pp_SMOKETEST
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice, _d("opacity adjustment"), &slice_opacity_adjustment);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice, _d("sort slices"), &sort_slices);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice, _d("show sorted slice labels"), &show_sort_labels);
#endif
#ifdef pp_FSEEK
    glui_bounds->add_checkbox_to_panel(ROLLOUT_slice, _d("incremental data loading"), &load_incremental,SLICE_LOAD_INCREMENTAL,LoadIncrementalCB);
    LoadIncrementalCB(SLICE_LOAD_INCREMENTAL);
#endif
    SliceBoundCB(FILETYPEINDEX);
  }

  ROLLOUT_time = glui_bounds->add_rollout_to_panel(PANEL_bounds,"Time", false, TIME_ROLLOUT, FileRolloutCB);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_time, TIME_ROLLOUT);

  PANEL_time1a = glui_bounds->add_panel_to_panel(ROLLOUT_time,"",false);
  SPINNER_timebounds=glui_bounds->add_spinner_to_panel(PANEL_time1a,_d("Time:"),GLUI_SPINNER_FLOAT,&glui_time);
  glui_bounds->add_column_to_panel(PANEL_time1a,false);
  SPINNER_timebounds->set_float_limits(0.0,3600.0*24);
  BUTTON_SETTIME=glui_bounds->add_button_to_panel(PANEL_time1a,_d("Set"),SET_TIME,TimeBoundCB);

  PANEL_time2 = glui_bounds->add_panel_to_panel(ROLLOUT_time,_d("Data loading"),true);

  PANEL_time2a = glui_bounds->add_panel_to_panel(PANEL_time2,"",false);
  SPINNER_tload_begin=glui_bounds->add_spinner_to_panel(PANEL_time2a,"min time",GLUI_SPINNER_FLOAT,&tload_begin,TBOUNDS,TimeBoundCB);
  glui_bounds->add_column_to_panel(PANEL_time2a,false);
  CHECKBOX_use_tload_begin=glui_bounds->add_checkbox_to_panel(PANEL_time2a,"",&use_tload_begin,TBOUNDS_USE,TimeBoundCB);

  PANEL_time2b = glui_bounds->add_panel_to_panel(PANEL_time2,"",false);
  SPINNER_tload_end=glui_bounds->add_spinner_to_panel(PANEL_time2b,"max time",GLUI_SPINNER_FLOAT,&tload_end,TBOUNDS,TimeBoundCB);
  glui_bounds->add_column_to_panel(PANEL_time2b,false);
  CHECKBOX_use_tload_end=glui_bounds->add_checkbox_to_panel(PANEL_time2b,"",&use_tload_end,TBOUNDS_USE,TimeBoundCB);

  PANEL_time2c = glui_bounds->add_panel_to_panel(PANEL_time2,"",false);
  SPINNER_tload_skip=glui_bounds->add_spinner_to_panel(PANEL_time2c,_d("frame skip"),GLUI_SPINNER_INT,&tload_skip,TBOUNDS,TimeBoundCB);
  glui_bounds->add_column_to_panel(PANEL_time2c,false);
  CHECKBOX_use_tload_skip=glui_bounds->add_checkbox_to_panel(PANEL_time2c,"",&use_tload_skip,TBOUNDS_USE,TimeBoundCB);
  SPINNER_tload_skip->set_int_limits(0,1000);

  glui_bounds->add_button_to_panel(PANEL_time2,_d("Reload all data"), RELOAD_ALL_DATA,TimeBoundCB);
  glui_bounds->add_button_to_panel(PANEL_time2, _d("Reload new data"), RELOAD_INCREMENTAL_DATA, TimeBoundCB);

  TimeBoundCB(TBOUNDS_USE);

#ifdef pp_MEMDEBUG
  ROLLOUT_memcheck = glui_bounds->add_rollout(_d("Memory check"),false,MEMCHECK_ROLLOUT,FileRolloutCB);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_memcheck, MEMCHECK_ROLLOUT);

  list_memcheck_index = 0;
  RADIO_memcheck = glui_bounds->add_radiogroup_to_panel(ROLLOUT_memcheck,&list_memcheck_index,MEMCHECK, MemcheckCB);
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"Unlimited");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"1 GB");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"2 GB");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"4 GB");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"8 GB");
#endif

  glui_bounds->add_button(_d("Save settings"), SAVE_SETTINGS, BoundsDlgCB);
  glui_bounds->add_button(_d("Close"), CLOSE_BOUNDS, BoundsDlgCB);

  glui_bounds->set_main_gfx_window( main_window );
}

/* ------------------ CompressOnOff ------------------------ */

extern "C" void CompressOnOff(int flag){
  switch(flag){
    case OFF:
      if(BUTTON_compress!=NULL)BUTTON_compress->disable();
      if(CHECKBOX_overwrite_all!=NULL)CHECKBOX_overwrite_all->disable();
      if(CHECKBOX_erase_all!=NULL)CHECKBOX_erase_all->disable();
      if(CHECKBOX_multi_task!=NULL)CHECKBOX_multi_task->disable();
      break;
    case ON:
      if(BUTTON_compress!=NULL)BUTTON_compress->enable();
      if(CHECKBOX_overwrite_all!=NULL)CHECKBOX_overwrite_all->enable();
      if(CHECKBOX_erase_all!=NULL)CHECKBOX_erase_all->enable();
      if(CHECKBOX_multi_task!=NULL)CHECKBOX_multi_task->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
  }
}

/* ------------------ Plot3DBoundCB ------------------------ */

extern "C" void Plot3DBoundCB(int var){
  int i;

  switch(var){
  case UNLOAD_QDATA:
    if(cache_qdata==0){
     ROLLOUT_isosurface->disable();
    }
    else{
      int enable_isosurface;

      enable_isosurface=1;
      for(i=0;i<nmeshes;i++){
        meshdata *meshi;
        plot3ddata *plot3di;

        meshi = meshinfo + i;
        if(meshi->plot3dfilenum==-1)continue;
        plot3di = plot3dinfo + meshi->plot3dfilenum;
        if(plot3di->loaded==0||plot3di->display==0)continue;
        if(meshi->qdata==NULL){
          enable_isosurface=0;
          break;
        }
      }
      if(enable_isosurface==1)ROLLOUT_isosurface->enable();
      if(enable_isosurface==0)ROLLOUT_isosurface->disable();
    }
    break;
  case PLOT3D_VECTORSKIP:
    if(SPINNER_slicevectorskip!=NULL)SPINNER_slicevectorskip->set_int_val(vectorskip);
    break;
  case UPDATE_VECTOR_FROM_SMV:
    if(SPINNER_vectorpointsize!=NULL&&SPINNER_vectorlinewidth!=NULL&&SPINNER_vectorlinelength!=NULL){
      SPINNER_vectorpointsize->set_float_val(vectorpointsize);
      SPINNER_vectorlinewidth->set_float_val(vectorlinewidth);
      SPINNER_vectorlinelength->set_float_val(vecfactor);
    }
    Plot3DBoundCB(UPDATE_VECTOR);
    break;
  case UPDATE_VECTOR:
    UpdatePlotSlice(XDIR);
    UpdatePlotSlice(YDIR);
    UpdatePlotSlice(ZDIR);
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    UpdateChopColors();
    switch(setp3chopmin_temp){
      case DISABLE:
        EDIT_p3_chopmin->disable();
        break;
      case ENABLE:
        EDIT_p3_chopmin->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    break;
  case SETCHOPMAXVAL:
    UpdateChopColors();
    switch(setp3chopmax_temp){
      case DISABLE:
        EDIT_p3_chopmax->disable();
        break;
      case ENABLE:
        EDIT_p3_chopmax->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    break;
  case CHOPVALMIN:
    p3chopmin[list_p3_index]=p3chopmin_temp;
    setp3chopmin[list_p3_index]=setp3chopmin_temp;

    UpdateChopColors();
    break;
  case CHOPVALMAX:
    p3chopmax[list_p3_index]=p3chopmax_temp;
    setp3chopmax[list_p3_index]=setp3chopmax_temp;

    UpdateChopColors();
    break;
  case PLOTISO:
    visiso = 1 - visiso;
    handleiso();
    glutPostRedisplay();
    break;
  case PLOTISOTYPE:
    updatemenu=1;
    break;
  case UPDATEPLOT:
    UpdateRGBColors(COLORBAR_INDEX_NONE);
    updatemenu=1;
    glutPostRedisplay();
    break;
  case FILETYPEINDEX:
   p3min[list_p3_index_old]=p3min_temp;
   p3max[list_p3_index_old]=p3max_temp;
   setp3min[list_p3_index_old]=setp3min_temp;
   setp3max[list_p3_index_old]=setp3max_temp;
   p3chopmin[list_p3_index_old]=p3chopmin_temp;
   p3chopmax[list_p3_index_old]=p3chopmax_temp;
   setp3chopmin[list_p3_index_old]=setp3chopmin_temp;
   setp3chopmax[list_p3_index_old]=setp3chopmax_temp;

   p3min_temp=p3min[list_p3_index];
   p3max_temp=p3max[list_p3_index];
   setp3min_temp=setp3min[list_p3_index];
   setp3max_temp=setp3max[list_p3_index];
   p3chopmin_temp=p3chopmin[list_p3_index];
   p3chopmax_temp=p3chopmax[list_p3_index];
   setp3chopmin_temp=setp3chopmin[list_p3_index];
   setp3chopmax_temp=setp3chopmax[list_p3_index];
   if(plot3dinfo!=NULL){
     plot3dmin_unit = (unsigned char *)plot3dinfo->label[list_p3_index].unit;
     plot3dmax_unit = plot3dmin_unit;
     UpdateGluiPlot3D_units();
   }

   EDIT_p3_min->set_float_val(p3min_temp);
   EDIT_p3_max->set_float_val(p3max_temp);
   EDIT_p3_chopmin->set_float_val(p3chopmin_temp);
   EDIT_p3_chopmax->set_float_val(p3chopmax_temp);

   list_p3_index_old=list_p3_index;
   RADIO_p3_setmin->set_int_val(setp3min_temp);
   RADIO_p3_setmax->set_int_val(setp3max_temp);
   CHECKBOX_p3_setchopmin->set_int_val(setp3chopmin_temp);
   CHECKBOX_p3_setchopmax->set_int_val(setp3chopmax_temp);
   Plot3DBoundCB(SETCHOPMINVAL);
   Plot3DBoundCB(SETCHOPMAXVAL);
   Plot3DBoundCB(SETVALMIN);
   Plot3DBoundCB(SETVALMAX);
   break;
  case SETVALMIN:
   switch(setp3min_temp){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      EDIT_p3_min->disable();
      break;
    case SET_MIN:
    case CHOP_MIN:
      EDIT_p3_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
   }
   break;
  case SETVALMAX:
     switch(setp3max_temp){
      case PERCENTILE_MIN:
      case GLOBAL_MIN:
        EDIT_p3_max->disable();
        break;
      case SET_MIN:
      case CHOP_MIN:
        EDIT_p3_max->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
     }
   break;
  case FILEUPDATE:
   p3min[list_p3_index] =    p3min_temp;
   p3max[list_p3_index] =    p3max_temp;
   setp3min[list_p3_index] = setp3min_temp;
   setp3max[list_p3_index] = setp3max_temp;
   break;
  case FILERELOAD:
   Plot3DBoundCB(FILEUPDATE);
   for(i=0;i<nplot3dinfo;i++){
     if(plot3dinfo[i].loaded==0)continue;
     LoadPlot3dMenu(i);
   }
   UpdateGlui();
   break;
  case VALMIN:
  case VALMAX:
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ UpdateTracers ------------------------ */

extern "C" void UpdateTracers(void){
  if(CHECKBOX_showtracer==NULL)return;
  CHECKBOX_showtracer->set_int_val(show_tracers_always);
}


/* ------------------ UpdateGluiIsotype ------------------------ */

extern "C" void UpdateGluiIsotype(void){
  CHECKBOX_show_iso_solid->set_int_val(visAIso&1);
  CHECKBOX_show_iso_outline->set_int_val((visAIso&2)/2);
  CHECKBOX_show_iso_verts->set_int_val((visAIso&4)/4);
}


/* ------------------ UpdateGluiPlot3Dtype ------------------------ */

extern "C" void UpdateGluiPlot3Dtype(void){
  RADIO_plot3d_isotype->set_int_val(p3dsurfacetype);
}
/* ------------------ UpdateChar ------------------------ */

extern "C" void UpdateChar(void){
  if(CHECKBOX_showchar==NULL)return;
  if(canshow_threshold==1){
    CHECKBOX_showchar->enable();
  }
  else{
    CHECKBOX_showchar->disable();
  }
  CHECKBOX_showchar->set_int_val(vis_threshold);
  BoundBoundCB(SHOWCHAR);
}

/* ------------------ UpdatePlot3dListIndex ------------------------ */

extern "C" void UpdatePlot3dListIndex(void){
  int i;

  if(RADIO_p3==NULL)return;
  i = RADIO_p3->get_int_val();
  if(i!=plotn-1){
    p3min[i]=p3min_temp;
    p3max[i]=p3max_temp;
    setp3min[i]=setp3min_temp;
    setp3max[i]=setp3max_temp;

    p3chopmin[i]=p3chopmin_temp;
    p3chopmax[i]=p3chopmax_temp;
    setp3chopmin[i]=setp3chopmin_temp;
    setp3chopmax[i]=setp3chopmax_temp;
  }

  i=plotn-1;
  list_p3_index_old=i;
  if(i<0)i=0;
  if(i>mxplot3dvars-1)i=mxplot3dvars-1;
  RADIO_p3->set_int_val(i);
  p3min_temp = p3min[i];
  p3max_temp = p3max[i];
  setp3min_temp = setp3min[i];
  setp3max_temp = setp3max[i];

  p3chopmin_temp = p3chopmin[i];
  p3chopmax_temp = p3chopmax[i];
  setp3chopmin_temp = setp3chopmin[i];
  setp3chopmax_temp = setp3chopmax[i];
  if(nplot3dinfo>0){
    Plot3DBoundCB(SETVALMIN);
    Plot3DBoundCB(SETVALMAX);
    Plot3DBoundCB(SETCHOPMINVAL);
    Plot3DBoundCB(SETCHOPMAXVAL);
  }
  UpdateChopColors();
  UpdateGlui();
}

/* ------------------ GetColorTableIndex ------------------------ */

int GetColorTableIndex(int *color){
  int i;

  if(colortableinfo==NULL)return -1;
  for(i=0;i<ncolortableinfo;i++){
    colortabledata *cti;

    cti = colortableinfo + i;
    if(color[0]==cti->color[0]&&color[1]==cti->color[1]&&color[2]==cti->color[2])return i;
  }
  return -1;
}

/* ------------------ GetColorTable ------------------------ */

colortabledata *GetColorTable(char *label){
  int i;

  if(label==NULL||strlen(label)==0)return NULL;
  for(i=0;i<ncolortableinfo;i++){
    colortabledata *cti;

    cti = colortableinfo + i;
    if(strcmp(label,cti->label)==0)return cti;
  }
  return NULL;
}

/* ------------------ IsoBoundCB ------------------------ */

extern "C" void IsoBoundCB(int var){
  int i;
  float *iso_color;

  switch(var){
  case COLORTABLE_LIST:
    if(i_colortable_list>=0){
      colortabledata *cti;

      cti = colortableinfo+i_colortable_list;
      glui_iso_colors[0] = cti->color[0];
      glui_iso_colors[1] = cti->color[1];
      glui_iso_colors[2] = cti->color[2];
      glui_iso_colors[3] = cti->color[3];
      IsoBoundCB(ISO_COLORS);
      if(SPINNER_iso_colors[0]!=NULL)SPINNER_iso_colors[0]->set_int_val(glui_iso_colors[0]);
      if(SPINNER_iso_colors[1]!=NULL)SPINNER_iso_colors[1]->set_int_val(glui_iso_colors[1]);
      if(SPINNER_iso_colors[2]!=NULL)SPINNER_iso_colors[2]->set_int_val(glui_iso_colors[2]);
      if(SPINNER_iso_colors[3]!=NULL)SPINNER_iso_colors[3]->set_int_val(glui_iso_colors[3]);
    }
    break;

  case ISO_LEVEL:
    iso_color = iso_colors+4*(glui_iso_level-1);
    glui_iso_colors[0] = CLAMP(255*iso_color[0]+0.1, 0, 255);
    glui_iso_colors[1] = CLAMP(255*iso_color[1]+0.1, 0, 255);
    glui_iso_colors[2] = CLAMP(255*iso_color[2]+0.1, 0, 255);
    glui_iso_colors[3] = CLAMP(255*iso_color[3]+0.1, 1, 255);

    if(SPINNER_iso_colors[0]!=NULL)SPINNER_iso_colors[0]->set_int_val(glui_iso_colors[0]);
    if(SPINNER_iso_colors[1]!=NULL)SPINNER_iso_colors[1]->set_int_val(glui_iso_colors[1]);
    if(SPINNER_iso_colors[2]!=NULL)SPINNER_iso_colors[2]->set_int_val(glui_iso_colors[2]);
    if(SPINNER_iso_colors[3]!=NULL)SPINNER_iso_colors[3]->set_int_val(glui_iso_colors[3]);
    if(LIST_colortable != NULL){
      i_colortable_list = CLAMP(GetColorTableIndex(glui_iso_colors), -1, ncolortableinfo - 1);
      LIST_colortable->set_int_val(i_colortable_list);
    }
    break;
  case GLOBAL_ALPHA:
    for(i = 0; i < MAX_ISO_COLORS; i++){
      iso_colors[4 * i + 3] = iso_transparency;
    }
    if(SPINNER_iso_colors[3]!=NULL)SPINNER_iso_colors[3]->set_int_val(glui_iso_transparency);
    IsoBoundCB(ISO_COLORS);
    break;
  case ISO_TRANSPARENCY:
    iso_transparency = ((float)glui_iso_transparency + 0.1) / 255.0;
    break;
  case ISO_COLORS:
    iso_color = iso_colors+4*(glui_iso_level-1);
    iso_color[0] = ((float)glui_iso_colors[0]+0.1)/255.0;
    iso_color[1] = ((float)glui_iso_colors[1]+0.1)/255.0;
    iso_color[2] = ((float)glui_iso_colors[2]+0.1)/255.0;
    iso_color[3] = ((float)glui_iso_colors[3]+0.1)/255.0;

    for(i = 0; i < MAX_ISO_COLORS; i++){
      float graylevel;

      graylevel = TOBW(iso_colors+4*i);
      iso_colorsbw[4 * i + 0] = graylevel;
      iso_colorsbw[4 * i + 1] = graylevel;
      iso_colorsbw[4 * i + 2] = graylevel;
      iso_colorsbw[4 * i + 3] = iso_colors[4 * i + 3];
    }
    UpdateIsoColors();
    if(LIST_colortable!=NULL){
      i_colortable_list = CLAMP(GetColorTableIndex(glui_iso_colors), -1, ncolortableinfo-1);
      LIST_colortable->set_int_val(i_colortable_list);
    }
    break;
  case FRAMELOADING:
    isoframestep_global=isoframeskip_global+1;
    isozipstep=isozipskip+1;
    updatemenu=1;
    break;
  case ISO_SURFACE:
  case  ISO_OUTLINE:
  case ISO_POINTS:
    visAIso= 1*show_iso_solid + 2*show_iso_outline + 4*show_iso_verts;
    updatemenu=1;
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ AddScriptList ------------------------ */

extern "C" void AddScriptList(char *file, int id){
  if(file!=NULL&&strlen(file)>0&&LIST_scriptlist!=NULL){
    LIST_scriptlist->add_item(id,file);
  }
}

/* ------------------ GluiScriptEnable ------------------------ */

extern "C" void GluiScriptEnable(void){
    BUTTON_script_start->enable();
    BUTTON_script_stop->enable();
    BUTTON_script_runscript->enable();
    LIST_scriptlist->enable();
    BUTTON_script_saveini->enable();
    BUTTON_script_setsuffix->enable();
    EDIT_ini->enable();
  }

/* ------------------ GluiScriptDisable ------------------------ */

extern "C"  void GluiScriptDisable(void){
    BUTTON_script_start->disable();
    BUTTON_script_stop->disable();
    BUTTON_script_runscript->disable();
    LIST_scriptlist->disable();
    BUTTON_script_saveini->disable();
    BUTTON_script_setsuffix->disable();
    EDIT_ini->disable();
  }

/* ------------------ UpdateBoundaryListIndex ------------------------ */

extern "C" void UpdateBoundaryListIndex(int patchfilenum){
  int i;
  if(RADIO_bf==NULL)return;
  for(i=0;i<npatch2;i++){
    patchdata *patchi;

    patchi = patchinfo + patchfilenum;
    if(strcmp(patchlabellist[i],patchi->label.shortlabel)==0){
      RADIO_bf->set_int_val(i);
      list_patch_index_old=list_patch_index;
      Global2LocalBoundaryBounds(patchlabellist[i]);
      RADIO_patch_setmin->set_int_val(setpatchmin);
      RADIO_patch_setmax->set_int_val(setpatchmax);
      EDIT_patch_min->set_float_val(patchmin);
      EDIT_patch_max->set_float_val(patchmax);

      CHECKBOX_patch_setchopmin->set_int_val(setpatchchopmin);
      CHECKBOX_patch_setchopmax->set_int_val(setpatchchopmax);
      EDIT_patch_chopmin->set_float_val(patchchopmin);
      EDIT_patch_chopmax->set_float_val(patchchopmax);

      if(setpatchmin==SET_MIN){
        EDIT_patch_min->enable();
      }
      else{
        EDIT_patch_min->disable();
      }
      if(setpatchmax==SET_MAX){
        EDIT_patch_max->enable();
      }
      else{
        EDIT_patch_max->disable();
      }

      if(setpatchchopmin==SET_MIN){
        EDIT_patch_chopmin->enable();
      }
      else{
        EDIT_patch_chopmin->disable();
      }
      if(setpatchchopmax==SET_MAX){
        EDIT_patch_chopmax->enable();
      }
      else{
        EDIT_patch_chopmax->disable();
      }
      return;
    }
  }
}

/* ------------------ UpdateBoundaryListIndex2 ------------------------ */

extern "C" void UpdateBoundaryListIndex2(char *label){
  int i;
  for(i=0;i<npatch2;i++){
    if(strcmp(patchlabellist[i],label)==0){
      UpdateBoundaryListIndex(patchlabellist_index[i]);
      break;
    }
  }
}

/* ------------------ UpdateGluiStreakValue ------------------------ */

extern "C" void UpdateGluiStreakValue(float rvalue){
  float_streak5value=rvalue;
  if(SPINNER_partstreaklength!=NULL){
    SPINNER_partstreaklength->set_float_val(rvalue);
    SPINNER_partstreaklength->set_float_limits(0.0,tmax_part);
  }
}

/* ------------------ PartBoundCB ------------------------ */

void PartBoundCB(int var){
  partpropdata *prop_new, *prop_old;

  prop_new = part5propinfo + ipart5prop;
  prop_old = part5propinfo + ipart5prop_old;
  switch(var){
  case VALMIN:
    if(setpartmax==SET_MAX)prop_new->user_max=partmax;
    break;
  case VALMAX:
    if(setpartmin==SET_MIN)prop_new->user_min=partmin;
    break;
  case FILETYPEINDEX:

    // save data from controls

    prop_old->setvalmin=setpartmin;
    prop_old->setvalmax=setpartmax;
    if(setpartmin==SET_MIN){
      prop_old->user_min=partmin;
    }
    if(setpartmax==SET_MAX){
      prop_old->user_max=partmax;
    }
    prop_old->setchopmin=setpartchopmin;
    prop_old->setchopmax=setpartchopmax;
    prop_old->chopmin=partchopmin;
    prop_old->chopmax=partchopmax;

    // copy data to controls

    setpartmin=prop_new->setvalmin;
    setpartmax=prop_new->setvalmax;
    PartBoundCB(SETVALMIN);
    PartBoundCB(SETVALMAX);

    setpartchopmin=prop_new->setchopmin;
    setpartchopmax=prop_new->setchopmax;
    partchopmin=prop_new->chopmin;
    partchopmax=prop_new->chopmax;

    partmin_unit = (unsigned char *)prop_new->label->unit;
    partmax_unit = partmin_unit;
    UpdateGluiPartUnits();

    // update controls

    if(RADIO_part_setmin!=NULL)RADIO_part_setmin->set_int_val(setpartmin);
    if(RADIO_part_setmax!=NULL)RADIO_part_setmax->set_int_val(setpartmax);


    if(EDIT_part_chopmin!=NULL)EDIT_part_chopmin->set_float_val(partchopmin);
    if(EDIT_part_chopmax!=NULL)EDIT_part_chopmax->set_float_val(partchopmax);
    if(CHECKBOX_part_setchopmin!=NULL)CHECKBOX_part_setchopmin->set_int_val(setpartchopmin);
    if(CHECKBOX_part_setchopmax!=NULL)CHECKBOX_part_setchopmax->set_int_val(setpartchopmax);

    ipart5prop_old = ipart5prop;

    if(CHECKBOX_part_setchopmin!=NULL)PartBoundCB(SETCHOPMINVAL);
    if(CHECKBOX_part_setchopmax!=NULL)PartBoundCB(SETCHOPMAXVAL);

    break;
  case STREAKLENGTH:
    UpdateStreakValue(float_streak5value-0.001);
    if(float_streak5value==0.0){
      streak5show=0;
    }
    else{
      streak5show=1;
    }
    updatemenu=1;
    break;
  case TRACERS:
    updatemenu=1;
    break;
  case FRAMELOADING:
    partframestep=partframeskip+1;
    evacframestep=evacframeskip+1;
    evacframestep=evacframeskip+1;
    updatemenu=1;
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    prop_new->setchopmin=setpartchopmin;
    prop_new->chopmin=partchopmin;
    UpdateChopColors();
    switch(setpartchopmin){
      case DISABLE:
      EDIT_part_chopmin->disable();
      break;
      case ENABLE:
      EDIT_part_chopmin->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case SETCHOPMAXVAL:
    prop_new->setchopmax=setpartchopmax;
    prop_new->chopmax=partchopmax;
    UpdateChopColors();
    switch(setpartchopmax){
      case DISABLE:
      EDIT_part_chopmax->disable();
      break;
      case ENABLE:
      EDIT_part_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case CHOPVALMIN:
    prop_new->setchopmin=setpartchopmin;
    prop_new->chopmin=partchopmin;
    if(EDIT_part_chopmin!=NULL)EDIT_part_chopmin->set_float_val(partchopmin);
    UpdateChopColors();
    break;
  case CHOPVALMAX:
    prop_new->setchopmax=setpartchopmax;
    prop_new->chopmax=partchopmax;
    if(EDIT_part_chopmax!=NULL)EDIT_part_chopmax->set_float_val(partchopmax);
    UpdateChopColors();
    break;
  case SETVALMIN:
    if(setpartmin_old==SET_MIN){
      if(prop_old!=NULL)prop_old->user_min=partmin;
    }
    setpartmin_old=setpartmin;
    switch(setpartmin){
    case PERCENTILE_MIN:
      if(prop_new!=NULL)partmin=prop_new->percentile_min;
      if(EDIT_part_min!=NULL)EDIT_part_min->disable();
      break;
    case GLOBAL_MIN:
      if(prop_new!=NULL)partmin=prop_new->global_min;
      if(EDIT_part_min!=NULL)EDIT_part_min->disable();
      break;
    case SET_MIN:
      if(prop_new!=NULL)partmin=prop_new->user_min;
      if(EDIT_part_min!=NULL)EDIT_part_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(prop_new!=NULL)prop_new->valmin=partmin;
    if(EDIT_part_min!=NULL)EDIT_part_min->set_float_val(partmin);
   break;
  case SETVALMAX:
    if(setpartmax_old==SET_MAX){
      if(prop_old!=NULL)prop_old->user_max=partmax;
    }
    setpartmax_old=setpartmax;
    switch(setpartmax){
    case PERCENTILE_MAX:
      if(prop_new!=NULL)partmax=prop_new->percentile_max;
      if(EDIT_part_max!=NULL)EDIT_part_max->disable();
      break;
    case GLOBAL_MAX:
      if(prop_new!=NULL)partmax=prop_new->global_max;
      if(EDIT_part_max!=NULL)EDIT_part_max->disable();
      break;
    case SET_MAX:
      if(prop_new!=NULL)partmax=prop_new->user_max;
      if(EDIT_part_max!=NULL)EDIT_part_max->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(prop_new!=NULL)prop_new->valmax=partmax;
    if(EDIT_part_max!=NULL)EDIT_part_max->set_float_val(partmax);
   break;
  case FILERELOAD:
    {
      int prop_index_SAVE;

     prop_index_SAVE=prop_index;
     PartBoundCB(FILETYPEINDEX);
     if(EDIT_part_min!=NULL&&setpartmin==SET_MIN)PartBoundCB(SETVALMIN);
     if(EDIT_part_max!=NULL&&setpartmax==SET_MAX)PartBoundCB(SETVALMAX);
     LoadParticleMenu(PARTFILE_RELOADALL);
     LoadEvacMenu(EVACFILE_LOADALL);
     UpdateGlui();
     ParticlePropShowMenu(prop_index_SAVE);
    }
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ SETslicemin ------------------------ */

void SETslicemin(int setslicemin_local, float slicemin_local, int setslicechopmin_local, float slicechopmin_local){
  if(slicebounds == NULL)return;
  slicebounds[list_slice_index].setvalmin = setslicemin_local;
  slicebounds[list_slice_index].valmin = slicemin_local;
  slicebounds[list_slice_index].setchopmin = setslicechopmin_local;
  slicebounds[list_slice_index].chopmin = slicechopmin_local;
}

/* ------------------ SETslicemax ------------------------ */

void SETslicemax(int setslicemax_local, float slicemax_local, int setslicechopmax_local, float slicechopmax_local){
  if(slicebounds == NULL)return;
  slicebounds[list_slice_index].setvalmax = setslicemax_local;
  slicebounds[list_slice_index].valmax = slicemax_local;
  slicebounds[list_slice_index].setchopmax = setslicechopmax_local;
  slicebounds[list_slice_index].chopmax = slicechopmax_local;
}

/* ------------------ SliceBoundCB ------------------------ */

extern "C" void SliceBoundCB(int var){
  int error,i;
  int ii;
  slicedata *sd;
  int last_slice;

  updatemenu=1;
  if(var==UPDATE_HISTOGRAM){
    update_slice_hists = 1;
    histograms_defined = 0;
    return;
  }
  if(var == INIT_HISTOGRAM){
    if(histogram_show_graph == 1 || histogram_show_numbers == 1){
      update_slice_hists = 1;
      visColorbar = 1;
    }
    return;
  }
  if(var==SLICE_IN_OBST){
    return;
  }
  if(var==DATA_transparent){
    if(CHECKBOX_transparentflag2!=NULL)CHECKBOX_transparentflag2->set_int_val(use_transparency_data);
    UpdateTransparency();
    UpdateChopColors();
    UpdateIsoControls();
    return;
  }

  if(var==COLORBAR_EXTREME2){
    UpdateExtreme();
    return;
  }
  if(var==COLORBAR_LIST2){
      selectedcolorbar_index= GetColorbarListIndex();
      UpdateColorbarList();
      ColorbarMenu(selectedcolorbar_index);
      ColorbarGlobal2Local();
  }
  if(var==COLORBAR_SMOOTH){
    updatemenu=1;
    return;
  }
  switch(var){
    case UPDATE_SLICEDUPS:
    updatemenu = 1;
    break;
    case SLICE_VECTORSKIP:
      if(SPINNER_plot3dvectorskip!=NULL)SPINNER_plot3dvectorskip->set_int_val(vectorskip);
      break;
    case ZONEVALMIN:
      GetZoneColors(zonetu, nzonetotal, izonetu,zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#ifdef pp_ZONETL
      GetZoneColors(zonetl, nzonetotal, izonetl, zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#endif
      zoneusermin=zonemin;
      break;
    case ZONEVALMAX:
      GetZoneColors(zonetu, nzonetotal, izonetu,zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#ifdef pp_ZONETL
      GetZoneColors(zonetl, nzonetotal, izonetl, zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#endif
      zoneusermax=zonemax;
      break;
    case SETZONEVALMIN:
      if(setzonemin==SET_MIN){
        EDIT_zone_min->enable();
        zonemin=zoneusermin;
        EDIT_zone_min->set_float_val(zonemin);
      }
      else{
        EDIT_zone_min->disable();
        EDIT_zone_min->set_float_val(zoneglobalmin);
      }
      GetZoneColors(zonetu, nzonetotal, izonetu,zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#ifdef pp_ZONETL
      GetZoneColors(zonetl, nzonetotal, izonetl, zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#endif
      break;
    case SETZONEVALMAX:
      if(setzonemax==SET_MAX){
        EDIT_zone_max->enable();
        zonemax=zoneusermax;
        EDIT_zone_max->set_float_val(zonemax);
      }
      else{
        EDIT_zone_max->disable();
        EDIT_zone_max->set_float_val(zoneglobalmax);
      }
      GetZoneColors(zonetu, nzonetotal, izonetu,zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#ifdef pp_ZONETL
      GetZoneColors(zonetl, nzonetotal, izonetl, zonemin, zonemax, nrgb, nrgb_full,
        colorlabelzone, zonescale, zonelevels256);
#endif
      break;
    case COLORBAR_LIST2:
      if(selectedcolorbar_index2 == bw_colorbar_index){
        setbwdata = 1;
        ColorbarMenu(bw_colorbar_index);
      }
      else{
        setbwdata = 0;
      }
      IsoBoundCB(ISO_COLORS);
      SetLabelControls();
      break;
    case RESEARCH_MODE:
      for(i=0;i<nsliceinfo;i++){
        slicedata *slicei;

        slicei = sliceinfo + i;
        if(slicei->loaded==0||slicei->display==0)continue;
        UpdateSliceList(GetSliceType(slicei));
        break;
      }
      if(research_mode==1){
        axislabels_smooth_save=axislabels_smooth;
        axislabels_smooth=0;
        visColorbar_save=visColorbar;
        visColorbar=1;

        // slice files

        if(nsliceloaded > 0){
          setslicemin_save = setslicemin;
          slicemin_save = slicemin;
          setslicemin = GLOBAL_MIN;
          SliceBoundCB(SETVALMIN);

          setslicemax_save = setslicemax;
          slicemax_save = slicemax;
          setslicemax = GLOBAL_MAX;
          SliceBoundCB(SETVALMAX);
        }

        // boundary files

        if(npatchloaded > 0){
          setpatchmin_save = setpatchmin;
          patchmin_save = patchmin;
          setpatchmin = GLOBAL_MIN;
          BoundBoundCB(SETVALMIN);

          setpatchmax_save = setpatchmax;
          patchmax_save = patchmax;
          setpatchmax = GLOBAL_MAX;
          BoundBoundCB(SETVALMAX);
          BoundBoundCB(FILERELOAD);
        }

        // particle files

        if(npartloaded>0){
          setpartmin_save = setpartmin;
          partmin_save = partmin;
          setpartmin = GLOBAL_MIN;
          PartBoundCB(SETVALMIN);

          setpartmax_save = setpartmax;
          partmax_save = partmax;
          setpartmax = GLOBAL_MAX;
          PartBoundCB(SETVALMAX);
          PartBoundCB(FILERELOAD);
        }

        // plot3d files

        if(nplot3dloaded>0){
          for(i = 0; i < MAXPLOT3DVARS; i++){
            setp3min_save[i] = setp3min[i];
            p3min_save[i] = p3min[i];
            setp3min[i] = GLOBAL_MIN;

            setp3max_save[i] = setp3max[i];
            p3max_save[i] = p3max[i];
            setp3max[i] = GLOBAL_MAX;
          }
          Plot3DBoundCB(SETVALMIN);
          Plot3DBoundCB(SETVALMAX);
          Plot3DBoundCB(FILERELOAD);
        }

        PRINTF("research mode on\n");
      }
      else{
        axislabels_smooth=axislabels_smooth_save;
        visColorbar=visColorbar_save;

        // slice files

        if(nsliceloaded > 0){
          setslicemin = setslicemin_save;
          SliceBoundCB(SETVALMIN);
          slicemin = slicemin_save;
          SliceBoundCB(VALMIN);

          setslicemax = setslicemax_save;
          SliceBoundCB(SETVALMAX);
          slicemax = slicemax_save;
          SliceBoundCB(VALMAX);
        }

        // boundary files

        if(npatchloaded > 0){
          setpatchmin = setpatchmin_save;
          BoundBoundCB(SETVALMIN);
          patchmin = patchmin_save;
          BoundBoundCB(VALMIN);

          setpatchmax = setpatchmax_save;
          BoundBoundCB(SETVALMAX);
          patchmax = patchmax_save;
          BoundBoundCB(VALMAX);
          BoundBoundCB(FILERELOAD);
        }

        // particle files

        if(npartloaded > 0){
          setpartmin = setpartmin_save;
          PartBoundCB(SETVALMIN);
          partmin = partmin_save;
          PartBoundCB(VALMIN);

          setpartmax = setpartmax_save;
          PartBoundCB(SETVALMAX);
          partmax = partmax_save;
          PartBoundCB(VALMAX);
          PartBoundCB(FILERELOAD);

          // particle files

          setpartmin = setpartmin_save;
          PartBoundCB(SETVALMIN);
          partmin = partmin_save;
          PartBoundCB(VALMIN);

          setpartmax = setpartmax_save;
          PartBoundCB(SETVALMAX);
          partmax = partmax_save;
          PartBoundCB(VALMAX);
          PartBoundCB(FILERELOAD);
        }

        // Plot3D files

        if(nplot3dloaded > 0){
          for(i = 0; i < MAXPLOT3DVARS; i++){
            setp3min[i] = setp3min_save[i];
            p3min[i] = p3min_save[i];

            setp3max[i] = setp3max_save[i];
            p3max[i] = p3max_save[i];
          }
          Plot3DBoundCB(SETVALMIN);
          Plot3DBoundCB(VALMIN);
          Plot3DBoundCB(SETVALMAX);
          Plot3DBoundCB(VALMAX);
          Plot3DBoundCB(FILERELOAD);
        }

        PRINTF("research mode off\n");
      }
      UpdateAxisLabelsSmooth();
      SliceBoundCB(FILEUPDATE);
      break;
#ifdef pp_BETA
    case SMOOTH_SURFACES:
      CHECKBOX_smooth2->set_int_val(smooth_iso_normal);
      break;
    case SORT_SURFACES:
      sort_geometry=sort_iso_triangles;
      for(i=nsurfinfo;i<nsurfinfo+MAX_ISO_COLORS+1;i++){
        surfdata *surfi;

        surfi = surfinfo + i;
        surfi->transparent_level=transparent_level;
      }
      CHECKBOX_sort2->set_int_val(sort_iso_triangles);
      break;
#endif
    case SHOW_EVAC_SLICES:
      data_evac_coloring = 1-constant_evac_coloring;
      UpdateSliceMenuShow();
      if(CHECKBOX_data_coloring!=NULL)CHECKBOX_data_coloring->set_int_val(data_evac_coloring);
      break;
    case DATA_EVAC_COLORING:
      constant_evac_coloring = 1-data_evac_coloring;
      UpdateSliceMenuShow();
      if(CHECKBOX_constant_coloring!=NULL)CHECKBOX_constant_coloring->set_int_val(constant_evac_coloring);
      break;
    case COLORBAND:
      UpdateRGBColors(colorbar_select_index);
      break;
    case TRANSPARENTLEVEL:
      for(i=nsurfinfo;i<nsurfinfo+MAX_ISO_COLORS+1;i++){
        surfdata *surfi;

        surfi = surfinfo + i;
        surfi->transparent_level=transparent_level;
      }
      UpdateRGBColors(COLORBAR_INDEX_NONE);
      if(SPINNER_transparent_level!=NULL)SPINNER_transparent_level->set_float_val(transparent_level);
      break;
    case LINE_CONTOUR_VALUE:
      if(slice_line_contour_num<1){
        slice_line_contour_num=1;
        SPINNER_line_contour_num->set_int_val(slice_line_contour_num);
      }
      if(slice_line_contour_num==1&&slice_line_contour_min!=slice_line_contour_max){
        slice_line_contour_max=slice_line_contour_min;
        SPINNER_line_contour_max->set_float_val(slice_line_contour_max);
      }
      slicebounds[list_slice_index].line_contour_min=slice_line_contour_min;
      slicebounds[list_slice_index].line_contour_max=slice_line_contour_max;
      slicebounds[list_slice_index].line_contour_num=slice_line_contour_num;
      break;
    case UPDATE_LINE_CONTOUR_VALUE:
      UpdateSliceContours(list_slice_index,slice_line_contour_min, slice_line_contour_max,slice_line_contour_num);
      break;
  case UPDATE_VECTOR_FROM_SMV:
    if(SPINNER_plot3d_vectorpointsize!=NULL&&SPINNER_plot3d_vectorlinewidth!=NULL&&SPINNER_plot3d_vectorlinelength!=NULL){
      SPINNER_plot3d_vectorpointsize->set_float_val(vectorpointsize);
      SPINNER_plot3d_vectorlinewidth->set_float_val(vectorlinewidth);
      SPINNER_plot3d_vectorlinelength->set_float_val(vecfactor);
    }
    SliceBoundCB(UPDATE_VECTOR);
    break;
  case UPDATE_VECTOR:
    break;
  case FRAMELOADING:
    sliceframestep=sliceframeskip+1;
    slicezipstep=slicezipskip+1;
    updatemenu=1;
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    UpdateChopColors();
    SETslicemin(setslicemin,slicemin,setslicechopmin,slicechopmin);
    switch(setslicechopmin){
      case DISABLE:
        EDIT_slice_chopmin->disable();
        break;
      case ENABLE:
        EDIT_slice_chopmin->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    break;
  case SETCHOPMAXVAL:
    UpdateChopColors();
    SETslicemax(setslicemax,slicemax,setslicechopmax,slicechopmax);
    switch(setslicechopmax){
      case DISABLE:
      EDIT_slice_chopmax->disable();
      break;
      case ENABLE:
      EDIT_slice_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case CHOPVALMIN:
    if(EDIT_slice_min!=NULL)EDIT_slice_min->set_float_val(slicemin);
    SETslicemin(setslicemin,slicemin,setslicechopmin,slicechopmin);
    UpdateChopColors();
    break;
  case CHOPVALMAX:
    if(EDIT_slice_max!=NULL)EDIT_slice_max->set_float_val(slicemax);
    SETslicemax(setslicemax,slicemax,setslicechopmax,slicechopmax);
    UpdateChopColors();
    break;
  case SETVALMIN:
    switch(setslicemin){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->disable();
      break;
    case SET_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(RADIO_slice_setmin!=NULL)RADIO_slice_setmin->set_int_val(setslicemin);
    SETslicemin(setslicemin,slicemin,setslicechopmin,slicechopmin);
    break;
  case SETVALMAX:
    switch(setslicemax){
      case PERCENTILE_MAX:
      case GLOBAL_MAX:
        if(EDIT_slice_max!=NULL)EDIT_slice_max->disable();
        break;
      case SET_MAX:
        if(EDIT_slice_max!=NULL)EDIT_slice_max->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    if(RADIO_slice_setmax!=NULL)RADIO_slice_setmax->set_int_val(setslicemax);
    SETslicemax(setslicemax,slicemax,setslicechopmax,slicechopmax);
    break;
  case VALMIN:
    if(EDIT_slice_min!=NULL)EDIT_slice_min->set_float_val(slicemin);
    SETslicemin(setslicemin,slicemin,setslicechopmin,slicechopmin);
    break;
  case VALMAX:
    if(EDIT_slice_max!=NULL)EDIT_slice_max->set_float_val(slicemax);
    SETslicemax(setslicemax,slicemax,setslicechopmax,slicechopmax);
    break;
  case FILETYPEINDEX:
    if(slice_bounds_dialog==1&&list_slice_index==fire_line_index){
      slice_bounds_dialog=0;
      if(ROLLOUT_slice_bound!=NULL){
        ROLLOUT_slice_bound->close();
        ROLLOUT_slice_bound->disable();
      }
      if(ROLLOUT_slice_chop!=NULL){
        ROLLOUT_slice_chop->close();
        ROLLOUT_slice_chop->disable();
      }
    }
    if(slice_bounds_dialog==0&&list_slice_index!=fire_line_index){
      slice_bounds_dialog=1;
      if(ROLLOUT_slice_bound!=NULL){
        ROLLOUT_slice_bound->enable();
      }
      if(ROLLOUT_slice_chop!=NULL){
        ROLLOUT_slice_chop->enable();
      }
    }
    SetSliceBounds(list_slice_index);
    if(EDIT_slice_min!=NULL)EDIT_slice_min->set_float_val(slicemin);
    switch(setslicemin){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->disable();
      break;
    case SET_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(EDIT_slice_max!=NULL)EDIT_slice_max->set_float_val(slicemax);
    switch(setslicemax){
    case PERCENTILE_MIN:
    case GLOBAL_MAX:
      if(EDIT_slice_max!=NULL)EDIT_slice_max->disable();
      break;
    case SET_MAX:
      if(EDIT_slice_max!=NULL)EDIT_slice_max->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }

    RADIO_slice_setmin->set_int_val(setslicemin);
    RADIO_slice_setmax->set_int_val(setslicemax);

    EDIT_slice_chopmin->set_float_val(slicechopmin);
    EDIT_slice_chopmax->set_float_val(slicechopmax);
    CHECKBOX_slice_setchopmin->set_int_val(setslicechopmin);
    CHECKBOX_slice_setchopmax->set_int_val(setslicechopmax);

    if(setslicechopmin==1){
      EDIT_slice_chopmin->enable();
    }
    else{
      EDIT_slice_chopmin->disable();
    }
    if(setslicechopmax==1){
      EDIT_slice_chopmax->enable();
    }
    else{
      EDIT_slice_chopmax->disable();
    }
    SPINNER_line_contour_min->set_float_val(slice_line_contour_min);
    SPINNER_line_contour_max->set_float_val(slice_line_contour_max);
    SPINNER_line_contour_num->set_int_val(slice_line_contour_num);
    break;
  case FILEUPDATE:
      for(ii = nslice_loaded - 1; ii >= 0; ii--){
        i = slice_loaded_list[ii];
        sd = sliceinfo + i;
        if(sd->type == islicetype){
          last_slice = i;
          break;
        }
      }
      for(ii = 0; ii < nslice_loaded; ii++){
        int set_slicecolor;

        i = slice_loaded_list[ii];
        sd = sliceinfo + i;
        if(sd->type == islicetype){
          set_slicecolor = DEFER_SLICECOLOR;
          if(i == last_slice)set_slicecolor = SET_SLICECOLOR;
          ReadSlice("", i, RESETBOUNDS, set_slicecolor, &error);
        }
      }
    break;
  case FILERELOAD:
    SliceBoundCB(FILEUPDATE);
    if(slicefilenum>=0&&slicefilenum<nsliceinfo){
      LoadSliceMenu(slicefilenum);
    }
    else{
      LoadSliceMenu(0);
    }
    UpdateGlui();
    break;
  case ALLFILERELOAD:
    ReloadAllSliceFiles();
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ UpdateSliceList ------------------------ */

extern "C" void UpdateSliceList(int index){
  RADIO_slice->set_int_val(index);
}

/* ------------------ UpdateSliceListIndex ------------------------ */

extern "C" void UpdateSliceListIndex(int sfn){
  int i;
  int slicefiletype;
  slicedata *sd;
  if(sfn<0){
    UpdateSliceFilenum();
    sfn=slicefilenum;
  }
  sd = sliceinfo+sfn;
  slicefiletype = GetSliceIndex(sd);
  if(slicefiletype>=0&&slicefiletype<nslice_type){
    i = slicefiletype;
    RADIO_slice->set_int_val(i);
    SetSliceBounds(i);
    list_slice_index=i;
    SliceBoundCB(SETVALMIN);
    SliceBoundCB(SETVALMAX);
    SliceBoundCB(VALMIN);
    SliceBoundCB(VALMAX);
    SliceBoundCB(SETCHOPMINVAL);
    SliceBoundCB(SETCHOPMAXVAL);
    SliceBoundCB(CHOPVALMIN);
    SliceBoundCB(CHOPVALMAX);
  }
}

/* ------------------ UpdateGlui ------------------------ */

extern "C" void UpdateGlui(void){
  GLUI_Master.sync_live_all();
}

/* ------------------ ShowGluiBounds ------------------------ */

extern "C" void ShowGluiBounds(int menu_id){
  int islice, ipatch;

  if(menu_id==DIALOG_BOUNDS){
    if(nsliceinfo>0){
      islice=RADIO_slice->get_int_val();
      SetSliceBounds(islice);
      SliceBoundCB(SETVALMIN);
      SliceBoundCB(SETVALMAX);
      SliceBoundCB(VALMIN);
      SliceBoundCB(VALMAX);
    }
    if(npatchinfo>0){
      ipatch=RADIO_bf->get_int_val();
      Global2LocalBoundaryBounds(patchlabellist[ipatch]);
      BoundBoundCB(SETVALMIN);
      BoundBoundCB(SETVALMAX);
    }
    if(npartinfo>0&&npartinfo!=nevac){
      PartBoundCB(SETVALMIN);
      PartBoundCB(SETVALMAX);
    }
    if(nplot3dinfo>0){
      Plot3DBoundCB(SETVALMIN);
      Plot3DBoundCB(SETVALMAX);
    }

    if(nsliceinfo>0||npatchinfo>0)UpdateGlui();

    UpdateChar();
    FileRolloutCB(FILEBOUNDS_ROLLOUT);
  }
  else if(menu_id == DIALOG_SHOWFILES){
    FileRolloutCB(SHOWHIDE_ROLLOUT);
  }
  else if(menu_id==DIALOG_CONFIG){
    FileRolloutCB(CONFIG_ROLLOUT);
  }
  else if(menu_id==DIALOG_AUTOLOAD){
    FileRolloutCB(LOAD_ROLLOUT);
  }
  else if(menu_id==DIALOG_TIME){
    FileRolloutCB(TIME_ROLLOUT);
  }
  else if(menu_id==DIALOG_SCRIPT){
    FileRolloutCB(SCRIPT_ROLLOUT);
  }
  else if(menu_id == DIALOG_SMOKEZIP){
    FileRolloutCB(COMPRESS_ROLLOUT);
  }
  else if(menu_id == DIALOG_3DSMOKE){
    FileRolloutCB(FILEBOUNDS_ROLLOUT);
    BoundRolloutCB(SMOKE3D_ROLLOUT);
  }
  glui_bounds->show();
}


/* ------------------ ShowBoundsDialog ------------------------ */

extern "C" void ShowBoundsDialog(int type){
  ShowGluiBounds(DIALOG_3DSMOKE);
  switch (type){
    case DLG_3DSMOKE:
      if(ROLLOUT_smoke3d!=NULL)ROLLOUT_smoke3d->open();
      break;
    case DLG_BOUNDARY:
      if(ROLLOUT_bound!=NULL)ROLLOUT_bound->open();
      break;
    case DLG_SLICE:
      if(ROLLOUT_slice != NULL)ROLLOUT_slice->open();
      break;
    case DLG_PART:
      if(ROLLOUT_part!=NULL)ROLLOUT_part->open();
      break;
    case DLG_PLOT3D:
      if(ROLLOUT_plot3d!=NULL)ROLLOUT_plot3d->open();
      break;
    case DLG_ISO:
      if(ROLLOUT_iso!=NULL)ROLLOUT_iso->open();
      break;
  }
}

/* ------------------ EnableBoundaryGlui ------------------------ */

extern "C" void EnableBoundaryGlui(void){
  ROLLOUT_boundary->enable();
}

/* ------------------ DisableBoundaryGlui ------------------------ */

extern "C" void DisableBoundaryGlui(void){
  ROLLOUT_boundary->disable();
}

/* ------------------ UpdateOverwrite ------------------------ */

extern "C" void UpdateOverwrite(void){
  if(CHECKBOX_overwrite_all!=NULL)CHECKBOX_overwrite_all->set_int_val(overwrite_all);
  if(CHECKBOX_compress_autoloaded!=NULL)CHECKBOX_compress_autoloaded->set_int_val(compress_autoloaded);
}

/* ------------------ HideGluiBounds ------------------------ */

extern "C" void HideGluiBounds(void){
  if(glui_bounds!=NULL)glui_bounds->hide();
}

/* ------------------ UpdateVectorWidgets ------------------------ */

extern "C" void UpdateVectorWidgets(void){
  Plot3DBoundCB(UPDATE_VECTOR_FROM_SMV);
  SliceBoundCB(UPDATE_VECTOR_FROM_SMV);
}

/* ------------------ UpdatePlot3dDisplay ------------------------ */

extern "C" void UpdatePlot3dDisplay(void){
  if(RADIO_plot3d_display!=NULL)RADIO_plot3d_display->set_int_val(contour_type);
}

/* ------------------ UpdateGluiTimeBounds ------------------------ */

extern "C" void UpdateGluiTimeBounds(float time_min, float time_max){
  if(SPINNER_timebounds!=NULL){
    SPINNER_timebounds->set_float_limits(time_min,time_max);
  }
}

/* ------------------ UpdateTBounds ------------------------ */

extern "C" void UpdateTBounds(void){
  settmin_p=use_tload_begin;
  settmax_p=use_tload_end;
  tmin_p=tload_begin;
  tmax_p=tload_end;

  settmin_s=use_tload_begin;
  settmax_s=use_tload_end;
  tmin_s=tload_begin;
  tmax_s=tload_end;

  settmin_i=use_tload_begin;
  settmax_i=use_tload_end;
  tmin_i=tload_begin;
  tmax_i=tload_end;

  settmin_s=use_tload_begin;
  settmax_s=use_tload_end;
  tmin_s=tload_begin;
  tmax_s=tload_end;

  settmin_b=use_tload_begin;
  settmax_b=use_tload_end;
  tmin_b=tload_begin;
  tmax_b=tload_end;

  if(use_tload_skip==1){
    smoke3dframeskip=tload_skip;
    boundframeskip=tload_skip;
    isoframeskip_global=tload_skip;
    partframeskip=tload_skip;
    evacframeskip=tload_skip;
    sliceframeskip=tload_skip;
  }
  else{
    smoke3dframeskip=0;
    boundframeskip=0;
    isoframeskip_global=0;
    partframeskip=0;
    evacframeskip=0;
    sliceframeskip=0;
  }

  Smoke3dBoundCB(FRAMELOADING);
  BoundBoundCB(FRAMELOADING);
  IsoBoundCB(FRAMELOADING);
  PartBoundCB(FRAMELOADING);
  SliceBoundCB(FRAMELOADING);
}

/* ------------------ UpdateFileLoad  ------------------------ */

extern "C" void UpdateFileLoad(void){
  int i;
  partdata *parti;
  slicedata *slicei;
  isodata *isoi;
  patchdata *patchi;
  smoke3ddata *smoke3di;
  plot3ddata *plot3di;
  vslicedata *vslicei;

  npartloaded = 0;
  nevacloaded = 0;
  for(i = 0; i < npartinfo; i++){
    parti = partinfo + i;
    if(parti->loaded == 1 && parti->evac == 0){
      npartloaded++;
    }
    if(parti->loaded == 1 && parti->evac == 1){
      nevacloaded++;
    }
  }

  nsliceloaded = 0;
  for(i = 0; i < nsliceinfo; i++){
    slicei = sliceinfo + i;
    if(slicei->loaded == 1){
      nsliceloaded++;
    }
  }

  nvsliceloaded = 0;
  for(i = 0; i < nvsliceinfo; i++){
    vslicei = vsliceinfo + i;
    if(vslicei->loaded == 1){
      nvsliceloaded++;
    }
  }

  nisoloaded = 0;
  for(i = 0; i < nisoinfo; i++){
    isoi = isoinfo + i;
    if(isoi->loaded == 1){
      nisoloaded++;
    }
  }

  npatchloaded = 0;
  for(i = 0; i < npatchinfo; i++){
    patchi = patchinfo + i;
    if(patchi->loaded == 1){
      npatchloaded++;
    }
  }

  nsmoke3dloaded = 0;
  for(i = 0; i < nsmoke3dinfo; i++){
    smoke3di = smoke3dinfo + i;
    if(smoke3di->loaded == 1){
      nsmoke3dloaded++;
    }
  }

  nplot3dloaded = 0;
  for(i = 0; i < nplot3dinfo; i++){
    plot3di = plot3dinfo + i;
    if(plot3di->loaded == 1){
      nplot3dloaded++;
    }
  }
}

/* ------------------ UpdateShowHideButtons ------------------------ */

extern "C" void UpdateShowHideButtons(void){

  UpdateFileLoad();
//  if(CHECKBOX_label_3 != NULL){
//    CHECKBOX_label_3->set_int_val(hide_overlaps);
//  }
  if(BUTTON_PART != NULL){
    if(npartloaded == 0){
      BUTTON_PART->disable();
    }
    else{
      BUTTON_PART->enable();
    }
  }

  if(BUTTON_SLICE != NULL){
    if(nsliceloaded == 0){
      BUTTON_SLICE->disable();
    }
    else{
      BUTTON_SLICE->enable();
    }
  }

  if(BUTTON_VSLICE != NULL){
    if(nvsliceloaded == 0){
      BUTTON_VSLICE->disable();
    }
    else{
      BUTTON_VSLICE->enable();
    }
  }

  if(BUTTON_ISO != NULL){
    if(nisoloaded == 0){
      BUTTON_ISO->disable();
    }
    else{
      BUTTON_ISO->enable();
    }
  }

  if(BUTTON_BOUNDARY != NULL){
    if(npatchloaded == 0){
      BUTTON_BOUNDARY->disable();
    }
    else{
      BUTTON_BOUNDARY->enable();
    }
  }

  if(BUTTON_3DSMOKE != NULL){
    if(nsmoke3dloaded == 0){
      BUTTON_3DSMOKE->disable();
    }
    else{
      BUTTON_3DSMOKE->enable();
    }
  }

  if(BUTTON_PLOT3D != NULL){
    if(nplot3dloaded == 0){
      BUTTON_PLOT3D->disable();
    }
    else{
      BUTTON_PLOT3D->enable();
    }
  }

  if(nplot3dloaded == 0 && nsmoke3dloaded == 0 && nisoloaded == 0 && nsliceloaded == 0 && npartloaded == 0 && npatchloaded == 0){
    if(RADIO_showhide != NULL)RADIO_showhide->disable();
  }
  else{
    if(RADIO_showhide != NULL)RADIO_showhide->enable();
  }
}
