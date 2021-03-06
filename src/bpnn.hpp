#ifndef BPNN_H
#define BPNN_H

#include <Eigen/Dense>

#include "../../mapreduce/mapreduce.hpp"

#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <random>
#include <algorithm>

class Layer {
public:
  Eigen::MatrixXf* contents;
  Eigen::MatrixXf* weights;
  Eigen::MatrixXf* v;
  Eigen::MatrixXf* bias;
  Eigen::MatrixXf* dZ;
  std::vector<Eigen::MatrixXf> prev_updates;
  std::function<float(float)> activation;
  std::function<float(float)> activation_deriv;
  char activation_str[1024];
  
  Layer(int rows, int columns);
  Layer(float* vals, int rows, int columns);
  void init_weights(Layer next);
};

class Network {
public:
  FILE* data;
  int instances;
  int test_instances;

  std::vector<Layer> layers;
  int length = 0;

  float epoch_acc;
  float epoch_cost;
  float val_acc;
  float val_cost;
  
  float learning_rate;
  float bias_lr;
  float lambda;
  int batch_size;

  int epochs = 0;
  int batches = 0;
  Eigen::MatrixXf* labels;

  std::function<float(float, float)> decay;

  Network(char* path, int batch_sz, float learn_rate, float bias_rate, float l, float ratio);
  void add_layer(int nodes, char* activation);
  void init_decay(char* type, float a_0, float k);
  void initialize();
  void update_layer(float* vals, int datalen, int index);
  void set_activation(int index, std::function<float(float)> custom, std::function<float(float)> custom_deriv);
  
  void feedforward();
  void list_net();

  float cost();
  float accuracy();
  void backpropagate();
  int next_batch();
  float test(char* path);
  void train();

  float get_acc();
  float get_cost();
  float get_val_acc();
  float get_val_cost();
};

void checks(Network net);
void demo(int total_epochs);
int prep_file(char* path, char* out_path);
int split_file(char* path, int lines, float ratio);

struct ValueError : public std::exception
{
  const char* message;
  const char* location;
  ValueError(const char* msg, const char* loc)
    :message{msg}, location{loc}
  {
  }
  const char* what() const throw () {
    char* error;
    sprintf(error, "%s (thrown in %s).", message, location);
    const char* error_message = error;
    return error_message;
  }
};

#define MAXLINE 1024
#define ZERO_THRESHOLD pow(10, -8) // for checks

#if (!RECKLESS)
#define checknan(x, loc) if(x==INFINITY || x==NAN || x == -INFINITY) throw ValueError("Detected NaN in operation", loc)
#else
#define checknan(x, loc)
#endif

#endif /* MODULE_H */
