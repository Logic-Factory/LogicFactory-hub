//
 // Created by zephyr on 2023/7/6.
 //
 
 #include "power.h"
 #include <chrono>
 #include <unistd.h>
 
 exact::Encoding
 exact::SSV_Power::encode(bool mark_variable, std::vector<double> input_probability_1, bool average = true) {
     int r = this->r, max_t =
             (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
     for (auto &function: functions)
         assert(function.num_bits == n);
     if(input_probability_1.size() == 0) {
         input_probability_1 = std::vector<double> (functions[0].num_bits, 0.5);
     }
 
     std::map<std::string, int> variable_index = generate_variable_index(n, r, max_t, m);
     Encoding result = generate_clauses(variable_index, n, r, max_t, m);
     if (mark_variable) {
         for (auto &entry: variable_index)
             result.add_comment("c " + entry.first + " " + std::to_string(entry.second) + "\n");
     }
 
     assert(result.check());
 
     result.num_variables_in_real = functions[0].num_bits + r;
     auto &clauses_in_real = result.clauses_in_real;
     assert(input_probability_1.size() == functions[0].num_bits);
     for (int i = 1; i <= input_probability_1.size(); i++) {
         clauses_in_real.emplace_back(
                 "(assert (= r" + std::to_string(i) + " " + std::to_string(input_probability_1[i - 1]) + "))");
     }
 
     for (int i = initial_i; i < initial_i + r; i++) {
         std::string temp_clause = "(assert (= r" + std::to_string(i) + " ";
         int count = 1;
         for (int k = 1; k < i; k++) {
             if (k > n && k < initial_i)continue;
             for (int j = 1; j < k; j++) {
                 if (j > n && j < initial_i)continue;
                 std::string sijk = "v" + std::to_string(
                         variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)]);
                 std::string fi11 = "v" + std::to_string(variable_index["f" + std::to_string(i) + "11"]);
                 std::string fi10 = "v" + std::to_string(variable_index["f" + std::to_string(i) + "10"]);
                 std::string fi01 = "v" + std::to_string(variable_index["f" + std::to_string(i) + "01"]);
                 std::string rj = "r" + std::to_string(j), rk = "r" + std::to_string(k);
                 std::string branch_result = "(+ 0 (+ (ite " + fi11 + " (* " + rj + " " + rk + ") 0) (+ (ite " + fi10 +
                                             " (* " + rj + " (- 1 " + rk + ")) 0) (ite " + fi01 + " (* (- 1 " + rj +
                                             ") " + rk + ") 0)"+
                                             ")))";
                 temp_clause += " (ite " + sijk + branch_result;
                 count++;
             }
         }
         temp_clause += " 0";
         for(int _i=0; _i<=count; _i++)
             temp_clause+=")";
         clauses_in_real.emplace_back(temp_clause);
         clauses_in_real.emplace_back("(assert (not (= r"+ std::to_string(i)+" "+ std::to_string(0)+")))");
     }
 
     if(average) {
         std::string temp_clause = "(assert (= r ( / (+ 0 ";
         for(int i=initial_i; i<initial_i+r; i++) {
             std::string variable = "r"+std::to_string(i);
             temp_clause += " (* "+ variable + " (- 1 " + variable + "))";
         }
         temp_clause += ") " + std::to_string(r) + ")))";
         clauses_in_real.emplace_back(temp_clause);
     } else {
         // WARNING: BUG EXIST; Need to verify the output gate index.
         clauses_in_real.emplace_back("(assert (= r (* r"+ std::to_string(initial_i+r-1)+" (- 1 r"+ std::to_string(initial_i+r-1) +"))))");
     }
 
     clauses_in_real.emplace_back("(assert (< r "+ std::to_string(target_switching_probability/2)+"))");
 
     return result;
 }
 
 
 
 exact::SSV_Power::SSV_Power(const std::vector<std::string> &functions): SSV(functions) {}
 
 exact::SSV_Power::SSV_Power(const std::vector<Boolean> &functions): SSV(functions) {}
 
 std::map<std::string, int> exact::SSV_Power::generate_variable_index(int n, int r, int max_t, int m) {
     return SSV::generate_variable_index(n, r, max_t, m);
 }
 
 void exact::generate_netlist_library_power(std::string const &output_file, int num_inputs, int num_classes, bool average = true, int start_index = 0, int partition_size = INT16_MAX) {
     std::string solver = "kissat";
     std::string encoding_method = "SSV";
     std::string symmetry = "";
     std::ifstream fin("./test_case/ssv_power/input.txt");
     assert(fin.is_open());
     std::string temp;
     int temp_int;
     std::map<std::string, int> lower_bound;
     std::vector<std::string> functions;
     int count = 0;
     while (fin >> temp >> temp_int) {
         //std::cout<<temp<<"\n";
         if(count >= start_index) {
             functions.emplace_back(temp);
             lower_bound[temp] = temp_int;
         }
         count++;
         if(count >= (start_index + partition_size))
             break;
     }
 
     std::ofstream fout(output_file, std::ios::out | std::ios::app);
     assert(fout.is_open());
     fout << "T 2\nA 1 "<<num_classes<<"\nS " << functions.size() << " " << num_inputs << "\n";
     fout.close();
 
     for (auto &line: functions) {
         exact::Boolean func(line);
         std::vector<exact::Boolean> funcs = {func};
         std::cout << "0x" << line << "\n";
         if (encoding_method != "SSV") {
             std::cerr << "Not Implemented Error";
             assert(false);
         }
         int num_label_indices = int(pow(num_classes, num_inputs));
         std::string last_result_str = "";
         for (int label_index = 0; label_index < num_label_indices; label_index++) {
             std::string result_str = "";
             fout = std::ofstream(output_file, std::ios::app | std::ios::out);
             assert(fout.is_open());
 
             exact::SSV_Power *encoder = new exact::SSV_Power(funcs);;
             encoder->num_classes = num_classes;
 
             if (symmetry.find('N') != std::string::npos) encoder->non_trivial = true;
             if (symmetry.find('A') != std::string::npos) encoder->all_steps = true;
             if (symmetry.find('R') != std::string::npos) encoder->no_replication = true;
             if (symmetry.find('C') != std::string::npos) encoder->lexicographical_step = true;
             if (symmetry.find('O') != std::string::npos) encoder->lexicographical_op = true;
             if (symmetry.find('S') != std::string::npos) encoder->ordered_symmetric = true;
 
             int local_label_index = label_index;
             std::vector<double> input_probability(num_inputs, 0);
             for(int k = 0; local_label_index > 0; k++) {
                 input_probability[num_inputs - k - 1] = (local_label_index%(num_classes))/double(num_classes);
                 local_label_index /= num_classes;
             }
             if(std::find(input_probability.begin(), input_probability.end(), 0.0) != input_probability.end())
                 continue;
 
             for(auto& entry: input_probability)
                 std::cout<<entry<<" ";
             //std::cout<<"\n";
 
             encoder->r = lower_bound[line];
             encoder->target_switching_probability = 1.0;
             std::pair<bool, std::vector<int>> result = power_synthesis(encoder, solver, std::cout, input_probability);
             std::string label = std::to_string(int(input_probability[0] / (1.0 / num_classes)));
             for (int i = 1; i < input_probability.size(); i++)
                 label += "+" + std::to_string(int(input_probability[i] / (1.0 / num_classes)));
 
             if(!result.first) {
                 result_str = "UNSAT";
                 if(result_str == last_result_str) continue;
                 else {
                     fout << "0x" << line << " ";
                     fout << label << " " << encoder->r << " ";
                     fout << "UNSAT\n";
                     last_result_str = result_str;
                     continue;
                 }
             }
             int r = encoder->r, max_t =
                     (1 << (func.num_bits)) - 1, m = (int) funcs.size(), n = func.num_bits;
             std::map<std::string, int> variable_index = encoder->generate_variable_index(n, r, max_t, m);
 
             std::map<int, bool> variable_assignment;
             for (auto &entry: result.second) {
                 int index = abs(entry);
                 variable_assignment[index] = index == entry;
             }
             if (encoding_method == "SSV") {
                 for (unsigned int i = encoder->initial_i; i < encoder->initial_i + r; i++) {
                     for (int k = 1; k < i; k++) {
                         for (int j = 1; j < k; j++) {
                             if (variable_assignment[variable_index["s" + std::to_string(i) + std::to_string(j) +
                                                                    std::to_string(k)]]) {
                                 result_str += std::to_string(j) + " " + std::to_string(k) + " ";
                                 //fout << j << " " << k << " ";
                                 bool f01 = variable_assignment[variable_index["f" + std::to_string(i) + "01"]],
                                         f10 = variable_assignment[variable_index["f" + std::to_string(i) + "10"]],
                                         f11 = variable_assignment[variable_index["f" + std::to_string(i) + "11"]];
                                 int function_one_hot = (f11 << 2) | (f10 << 1) | f01, function_type;
                                 switch (function_one_hot) {
                                     case 0:
                                         assert(false);
                                     case 1:
                                     case 2:
                                         function_type = 7;
                                         break;
                                     case 3:
                                         function_type = 14;
                                         break;
                                     case 4:
                                         function_type = 9;
                                         break;
                                     case 5:
                                         function_type = 13;
                                         break;
                                     case 6:
                                         function_type = 12;
                                         break;
                                     case 7:
                                         function_type = 4;
                                         break;
                                     default:
                                         assert(false);
                                 }
                                 result_str += std::to_string(function_type) + " ";
                                 //fout << function_type << " ";
                             }
                         }
                     }
                 }
                 result_str += std::to_string(r+num_inputs) + "\n";
                 //fout << r + num_inputs << "\n";
                 if(last_result_str == result_str)
                     continue;
                 else {
                     last_result_str = result_str;
                     fout << "0x" << line << " ";
                     fout << label << " " << encoder->r << " ";
                     fout << result_str;
                 }
                 fout.close();
                 delete encoder;
             } else {
                 std::cerr << "Not Implemented Error";
                 assert(false);
             }
         }
     }
     fin.close();
 
     fout = std::ofstream(output_file, std::ios::app | std::ios::out);
     assert(fout.is_open());
     fout << "E\n";
     fout.close();
 }




 void exact::generate_netlist_library_power_new(std::string const &input_file, std::string const &output_file, int num_inputs, int num_classes, bool average = true, int start_index = 0, int partition_size = INT16_MAX) {
     std::string solver = "kissat";
     std::string encoding_method = "SSV";
     std::string symmetry = "";
     std::ifstream fin(input_file);
     assert(fin.is_open());
     std::string temp;
     int temp_int;
     std::map<std::string, int> lower_bound;
     std::vector<std::string> functions;
     int count = 0;
     while (fin >> temp >> temp_int) {
         //std::cout<<temp<<"\n";
         if(count >= start_index) {
             functions.emplace_back(temp);
             lower_bound[temp] = temp_int;
         }
         count++;
         if(count >= (start_index + partition_size))
             break;
     }
 
     std::ofstream fout(output_file, std::ios::out | std::ios::app);
     assert(fout.is_open());
     fout << "T 2\nA 1 "<<num_classes<<"\nS " << functions.size() << " " << num_inputs << "\n";
     fout.close();
 
     for (auto &line: functions) {
         exact::Boolean func(line);
         std::vector<exact::Boolean> funcs = {func};
         std::cout << "0x" << line << "\n";
         if (encoding_method != "SSV") {
             std::cerr << "Not Implemented Error";
             assert(false);
         }
         int num_label_indices = int(pow(num_classes, num_inputs));
         std::string last_result_str = "";
         for (int label_index = 0; label_index < num_label_indices; label_index++) {
             std::string result_str = "";
             fout = std::ofstream(output_file, std::ios::app | std::ios::out);
             assert(fout.is_open());
 
             exact::SSV_Power *encoder = new exact::SSV_Power(funcs);;
             encoder->num_classes = num_classes;
 
             if (symmetry.find('N') != std::string::npos) encoder->non_trivial = true;
             if (symmetry.find('A') != std::string::npos) encoder->all_steps = true;
             if (symmetry.find('R') != std::string::npos) encoder->no_replication = true;
             if (symmetry.find('C') != std::string::npos) encoder->lexicographical_step = true;
             if (symmetry.find('O') != std::string::npos) encoder->lexicographical_op = true;
             if (symmetry.find('S') != std::string::npos) encoder->ordered_symmetric = true;
 
             int local_label_index = label_index;
             std::vector<double> input_probability(num_inputs, 0);
             for(int k = 0; local_label_index > 0; k++) {
                 input_probability[num_inputs - k - 1] = (local_label_index%(num_classes))/double(num_classes);
                 local_label_index /= num_classes;
             }
             if(std::find(input_probability.begin(), input_probability.end(), 0.0) != input_probability.end())
                 continue;
 
             for(auto& entry: input_probability)
                 std::cout<<entry<<" ";
             //std::cout<<"\n";
 
             encoder->r = lower_bound[line];
             encoder->target_switching_probability = 1.0;
             std::pair<bool, std::vector<int>> result = power_synthesis(encoder, solver, std::cout, input_probability);
             std::string label = std::to_string(int(input_probability[0] / (1.0 / num_classes)));
             for (int i = 1; i < input_probability.size(); i++)
                 label += "+" + std::to_string(int(input_probability[i] / (1.0 / num_classes)));
 
             if(!result.first) {
                 result_str = "UNSAT";
                 if(result_str == last_result_str) continue;
                 else {
                     fout << "0x" << line << " ";
                     fout << label << " " << encoder->r << " ";
                     fout << "UNSAT\n";
                     last_result_str = result_str;
                     continue;
                 }
             }
             int r = encoder->r, max_t =
                     (1 << (func.num_bits)) - 1, m = (int) funcs.size(), n = func.num_bits;
             std::map<std::string, int> variable_index = encoder->generate_variable_index(n, r, max_t, m);
 
             std::map<int, bool> variable_assignment;
             for (auto &entry: result.second) {
                 int index = abs(entry);
                 variable_assignment[index] = index == entry;
             }
             if (encoding_method == "SSV") {
                 for (unsigned int i = encoder->initial_i; i < encoder->initial_i + r; i++) {
                     for (int k = 1; k < i; k++) {
                         for (int j = 1; j < k; j++) {
                             if (variable_assignment[variable_index["s" + std::to_string(i) + std::to_string(j) +
                                                                    std::to_string(k)]]) {
                                 result_str += std::to_string(j) + " " + std::to_string(k) + " ";
                                 //fout << j << " " << k << " ";
                                 bool f01 = variable_assignment[variable_index["f" + std::to_string(i) + "01"]],
                                         f10 = variable_assignment[variable_index["f" + std::to_string(i) + "10"]],
                                         f11 = variable_assignment[variable_index["f" + std::to_string(i) + "11"]];
                                 int function_one_hot = (f11 << 2) | (f10 << 1) | f01, function_type;
                                 switch (function_one_hot) {
                                     case 0:
                                         assert(false);
                                     case 1:
                                     case 2:
                                         function_type = 7;
                                         break;
                                     case 3:
                                         function_type = 14;
                                         break;
                                     case 4:
                                         function_type = 9;
                                         break;
                                     case 5:
                                         function_type = 13;
                                         break;
                                     case 6:
                                         function_type = 12;
                                         break;
                                     case 7:
                                         function_type = 4;
                                         break;
                                     default:
                                         assert(false);
                                 }
                                 result_str += std::to_string(function_type) + " ";
                                 //fout << function_type << " ";
                             }
                         }
                     }
                 }
                 result_str += std::to_string(r+num_inputs) + "\n";
                 //fout << r + num_inputs << "\n";
                 if(last_result_str == result_str)
                     continue;
                 else {
                     last_result_str = result_str;
                     fout << "0x" << line << " ";
                     fout << label << " " << encoder->r << " ";
                     fout << result_str;
                 }
                 fout.close();
                 delete encoder;
             } else {
                 std::cerr << "Not Implemented Error";
                 assert(false);
             }
         }
     }
     fin.close();
 
     fout = std::ofstream(output_file, std::ios::app | std::ios::out);
     assert(fout.is_open());
     fout << "E\n";
     fout.close();
 }

