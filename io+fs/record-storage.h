struct rec {
  char name[256];
  int  account_number;
  double size_in_meter;
};

int usage(char *argv0, char *message);

const char *help_text = "%s\n\nUsage:\n\n%s W position name account size\n\n%s R position\n\n";
