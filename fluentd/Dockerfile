FROM fluent/fluentd

USER root

RUN gem install fluent-plugin-redis

COPY fluent.conf /fluentd/etc/fluent.conf

USER fluent