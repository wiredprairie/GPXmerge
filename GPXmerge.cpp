// GPXmerge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pugixml.hpp"
#include <iostream>
#include <string>
#include "dirent.h"
#include "helpers.h"
#include "boost/algorithm/string.hpp"
#include <vector>
#include <memory>
#include <map>

using namespace pugi;
using namespace std;

#ifdef _WIN32
const std::string os_folder_separator("\\");
#elif
const std::string os_folder_separator("/");
#endif

typedef shared_ptr<xml_document> xml_document_ptr;

int _tmain(int argc, _TCHAR* argv[])
{
	vector<xml_document_ptr> gpxDocs;
	map<string, xml_node> trkseg_map;
	
	DIR *pDir;
	dirent *pEnt;
	xml_document_ptr first_doc;

	if (argc < 2) {
		cout << "GPXMerge - merges GPX files into a single file." << endl ;	
		cout << "GPXMERGE source-path" << endl;
		cout << "  source-path         Specifies the folder to non-recursively search." << endl;
		cout << "                      All files with the extension .GPX are merged" << endl;
		cout << "                      into a single GPX file named MERGED.GPX." << endl << endl;
		cout << "Skips duplicate segments." << endl << endl;
		return EXIT_FAILURE;
	}
	string start_dir(argv[1]);

	auto last_char = start_dir.back();
	if (last_char != os_folder_separator.at(0)) {
		start_dir.append(os_folder_separator);
	}
	if ((pDir = opendir (start_dir.c_str())) != NULL) {
		xml_document temp;
		auto temp_trk_seg_nodes = temp.append_child("all_tracks");
		/* print all the files and directories within directory */
		while ((pEnt = readdir (pDir)) != NULL) {
			string file_name(pEnt->d_name);
			auto pos = file_name.rfind(".");
			
			if (pos != 0 && pos != file_name.size() - 1) {
				string ext;
				ext.append(file_name.begin() + pos, file_name.end());
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				if (hasEnding(ext, ".gpx2")) {
					int segments = 0;
					auto doc = make_shared<xml_document>();
					if (!first_doc) {
						first_doc = doc;
					}					
					file_name.insert(0, start_dir);
					auto result = doc->load_file(file_name.c_str());
															
					if (result.status == xml_parse_status::status_ok) {
						gpxDocs.push_back(doc);
						auto gpx = doc->child("gpx");

						if (gpx) {
							if (auto trk = gpx.child("trk")) {
								string name(trk.child("name").value());
								std::cout << name << endl;
								for (auto trkseg_node = trk.child("trkseg"); trkseg_node; trkseg_node = trkseg_node.next_sibling("trkseg")) {
									auto first_seg = trkseg_node.child("trkpt");
									if (first_seg) {
										if(auto time_node = first_seg.child("time")) {
											auto time = string(time_node.first_child().value());
											if (time.size() > 0) {
												// if there's more than one at a time,
												// it's lost (but how did that happen anyway?)
												auto copy = temp_trk_seg_nodes.append_copy(trkseg_node);
												trkseg_map[time] = copy;
												++segments;
											}
										}										
									}

								}
								// remove all trksegs!
								while(trk.remove_child("trkseg"));
							}							
						}
						std::cout << "Parsed " << file_name << " with " << segments << " segments." << endl;
					}
				}
			}
		}
		// make sure handles are closed
		closedir (pDir);

		// uses the first document as a master/template for the merged file 
		if (first_doc) {
			auto gpx = first_doc->child("gpx");
			auto trk_node = gpx.child("trk");
			// grab everything from the map and put it into the doc
			for(auto it=trkseg_map.begin(); it != trkseg_map.end(); ++it) {
				trk_node.append_copy(it->second);
			}
			string path("merged.gpx");
			path.insert(0, start_dir);
			first_doc->save_file(path.c_str());		
		} else {
			cout << "No gpx files found." << endl;
			return EXIT_FAILURE;
		}
	} else {
		cout << "Error, could not open directory." << endl;
		return EXIT_FAILURE;
	}

#if DEBUG
	string pause;
	getline(cin, pause);
#endif
	return EXIT_SUCCESS;
}

