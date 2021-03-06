#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "bpnn.hpp"
namespace py = pybind11;

// struct pair* map (struct pair input_pair)
// {
//   char* path = new char[100];
//   strcpy(path, (char*)input_pair.key);
//   strcat(path, "_shuf");
//   printf("%s and %s\n", path, (char*)input_pair.key);
//   int linecount = prep_file((char*)input_pair.key, path);
//   Network* net = new Network (path, 4, 2, 1, 5, 10, 2);  
//   auto begin = std::chrono::high_resolution_clock::now();
//   // std::cout << "\n\n\n";
//   float epoch_cost = 1000;
//   float epoch_accuracy = -1;
//   int epochs = 0;
//   int total_epochs = 50;
//   net->batches= 0;
//   // net.feedforward();
//   // net.backpropagate();
//   // std::cout << net.cost() << "\n";

//   printf("Beginning train on %i instances for %i epochs...\n", linecount, 50);
//   while (epochs < total_epochs) {
//     auto ep_begin = std::chrono::high_resolution_clock::now();
//     // int linecount = prep_file("./data_banknote_authentication.txt");
//     float cost_sum = 0;
//     float acc_sum = 0;
//     double times[5] = {0};
//     for (int i = 0; i <= linecount-net->batch_size; i+=net->batch_size) {
//       // auto feed_begin = std::chrono::high_resolution_clock::now();
//       net->feedforward();
//       // auto back_begin = std::chrono::high_resolution_clock::now();
//       net->backpropagate();
//       // auto cost_begin = std::chrono::high_resolution_clock::now();
//       cost_sum += net->cost();
//       // std::cout << acc_sum << " "<< net.accuracy() << " " << net.batch_size << "\n";
//       // auto acc_begin = std::chrono::high_resolution_clock::now();
//       acc_sum += net->accuracy();
//       // std::cout << net.cost() << " as it is " << net.labels[0] << " vs " << *net.layers[net.length-1].contents << "\n";
//       // auto batch_begin = std::chrono::high_resolution_clock::now();

//       if (i != linecount-net->batch_size) { // Don't try to advance batch on final batch.
//         net->next_batch();
//       }
//       net->batches++;
//       // auto loop_end = std::chrono::high_resolution_clock::now();
//       // times[0] += std::chrono::duration_cast<std::chrono::nanoseconds>(back_begin -feed_begin).count() / pow(10,9);
//       // times[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(cost_begin - back_begin).count() / pow(10,9);
//       // times[2] += std::chrono::duration_cast<std::chrono::nanoseconds>(acc_begin - cost_begin).count() / pow(10,9);
//       // times[3] += std::chrono::duration_cast<std::chrono::nanoseconds>(batch_begin - acc_begin).count() / pow(10,9);
//       // times[4] += std::chrono::duration_cast<std::chrono::nanoseconds>(loop_end - batch_begin).count() / pow(10,9);
//     }
//     epoch_accuracy = 1.0/((float) linecount/net->batch_size) * acc_sum;
//     epoch_cost = 1.0/((float) linecount/net->batch_size) * cost_sum;
//     auto ep_end = std::chrono::high_resolution_clock::now();
//     double epochtime = (double) std::chrono::duration_cast<std::chrono::nanoseconds>(ep_end-ep_begin).count() / pow(10,9);
//     printf("Epoch %i/%i - time %f - cost %f - acc %f\n", epochs+1, total_epochs, epochtime, epoch_cost, epoch_accuracy);
//     // printf("Avg time spent across %i batches: %lf on feedforward, %lf on backprop, %lf on cost, %lf on acc, %lf on next batch.\n", net.batches, times[0]/net.batches, times[1]/net.batches, times[2]/net.batches, times[3]/net.batches, times[4]/net.batches);
//     // printf("Time spent across epoch: %lf on feedforward, %lf on backprop, %lf on cost, %lf on acc, %lf on next batch, %lf other.\n", times[0], times[1], times[2], times[3], times[4], epochtime-times[0]-times[1]-times[2]-times[3]-times[4]);
//     net->batches=1;
//     epochs++;
//   }
//   struct pair* output = new struct pair;
//   char* key = new char[100];
//   strcpy(key, path);
//   output[0].key = key;
//   output[0].value = net;
//   return output;
// }

// struct pair* reduce (struct pair* input_pairs)
// {
//   struct pair* output = new struct pair[6];  
//   for (int i = 0; input_pairs[i].key != 0x0; i++) {
//     float* acc = new float;
//     *acc = ((Network*)input_pairs[i].value)->test("./test.txt");
//     output[i].key = input_pairs[i].key;
//     output[i].value = acc;
//   }
//   return output;
// }

// void translate(char* path)
// {
//   FILE* rptr = fopen(path, "r");
//   FILE* wptr = fopen("./translated", "w");
//   char* line = new char[MAXLINE];
//   char* newline = new char[MAXLINE];
//   while (fgets(line, MAXLINE, rptr) != NULL) {
//     void* addr1;
//     void* addr2;
//     sscanf(line, "%p %p", &addr1, &addr2);
//     sprintf(newline, "%s %f", (char*)addr1, *(float*)addr2);
//     int batch_num = strtol((char*)addr1, NULL, 10);
//     fprintf(wptr, "%s %f\n",(char*)addr1, *(float*)addr2);
//   }
//   fclose(rptr);
//   fclose(wptr);
//   free(newline);
//   free(line);
// }

PYBIND11_MODULE(mrbpnn, m) {
  m.doc() = "Fast machine learning in C++"; // optional module docstring
 
  py::class_<Network>(m, "Network")
    .def(py::init<char*, int, float, float, float, float>())
    .def("add_layer", &Network::add_layer, py::arg("nodes"), py::arg("activation"))
    .def("initialize", &Network::initialize)
    .def("init_decay", &Network::init_decay, py::arg("type"), py::arg("a_0"), py::arg("k"))
    .def("set_activation", &Network::set_activation)
    .def("feedforward", &Network::feedforward)
    .def("backpropagate", &Network::backpropagate)
    .def("list_net", &Network::list_net)
    .def("cost", &Network::cost)
    .def("accuracy", &Network::accuracy)
    .def("update_layer", &Network::update_layer, py::arg("vals"), py::arg("len"), py::arg("index"))
    .def("next_batch", &Network::next_batch)
    .def("train", &Network::train)
    .def("get_acc", &Network::get_acc)
    .def("get_cost", &Network::get_cost)
    .def("get_val_acc", &Network::get_val_acc)
    .def("get_val_cost", &Network::get_val_cost);
}
